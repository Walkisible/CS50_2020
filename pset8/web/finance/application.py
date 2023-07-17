import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, pass_check, shares_check

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get username and message from session
    username = session["username"]
    tmp_message = session["message"]

    # Create message dictionary element
    message = {
        "message": tmp_message
    }

    # Update stock price everytime GET index.html
    updates = db.execute("SELECT symbol, shares FROM stock_port WHERE username = :username",
                         username=username)

    for update in updates:
        tmp = lookup(update["symbol"])
        new_TOTAL = float(tmp["price"]) * int(update["shares"])
        new_TOTAL = format(new_TOTAL, ".2f")
        db.execute("UPDATE stock_port SET price = :price, TOTAL = :TOTAL WHERE username = :username AND symbol = :symbol",
                   price=tmp["price"], TOTAL=new_TOTAL, username=username, symbol=update["symbol"])

    # Query data from stock_port table
    info = db.execute("SELECT symbol, name, shares, price, TOTAL FROM stock_port WHERE username = :username",
                      username=username)

    # Query data from users table
    cash = db.execute("SELECT cash FROM users WHERE username = :username",
                      username=username)

    # Calaculate grand total
    tmp_grand_TOTAL = []

    tmp_grand_TOTAL.append(cash[0]["cash"])

    i = 0
    for x in info:
        tmp_grand_TOTAL.append(info[i]["TOTAL"])
        i = i + 1

    tmp_cal = sum(tmp_grand_TOTAL)
    tmp_cal = format(tmp_cal, ".2f")

    grand_TOTAL = {
        "grand_TOTAL": tmp_cal
    }

    # Standardize current format (2 decimal point)
    tmpCash = cash[0]["cash"]
    tmpCash = format(tmpCash, ".2f")

    tmp_cash = {
        "cash": tmpCash
    }

    # Create list to store message and user's cash
    display01 = []

    display01.append(message)
    display01.append(tmp_cash)
    display01.append(grand_TOTAL)

    # Create list to store port information
    display02 = []

    i = 0

    for x in info:
        display02.append(info[i])
        i = i + 1

    return render_template("index.html", display01=display01, display02=display02)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via GET
    if request.method == "GET":
        return render_template("buy.html")

    else:
        # Get username from session
        username = session["username"]

        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 403)

        # Ensure shares was submitted correctly
        shares = request.form.get("shares")
        SharesCheck = shares_check(shares)

        if SharesCheck == False:
            return apology("shares must be in non-decimal number format", 403)

        if not shares or int(shares) < 1:
            return apology("must provide positive non-decimal number of shares", 403)

        # Ensure this stock is available
        data = lookup(request.form.get("symbol"))

        if data == None:
            return apology("must provide correct symbol", 403)

        # Get available cash from users table
        tmp_cash = db.execute("SELECT cash FROM users WHERE username = :username", username=username)

        # Neutralize user's data into key value format
        cash = float(tmp_cash[0]["cash"])
        b_price = float(data["price"])
        b_shares = int(shares)

        # Calculate
        bought = b_price * b_shares
        changed = cash - bought

        # Ensure user's cash is enough to buy stock
        if cash < bought:
            return apology("your cash is not enough to buy", 403)

        # Recording buy history
        db.execute("INSERT INTO history (username, symbol, price, shares) VALUES (:username, :symbol, :price, :shares)",
                   username=username, symbol=data["symbol"], price=data["price"], shares=shares)

        # Update users table
        db.execute("UPDATE users SET cash = :cash WHERE username = :username",
                   cash=changed, username=username)

        # Get symbol from stock_port table
        stock = db.execute("SELECT symbol FROM stock_port WHERE username = :username AND symbol = :symbol",
                           username = username, symbol=symbol)

        # Stock checking, if this stock wasn't bought before
        if len(stock) == 0:
            TOTAL = bought
            db.execute("INSERT INTO stock_port (username, symbol, name, price, shares, TOTAL) VALUES (:username, :symbol, :name, :price, :shares, :TOTAL)",
                       username=username, symbol=data["symbol"], name=data["name"], price=data["price"], shares=shares, TOTAL=TOTAL)

        # Stock checking, if this stock was bought before
        else:
            tmp_shares = db.execute("SELECT shares FROM stock_port WHERE username = :username AND symbol = :symbol",
                                    username=username, symbol=symbol)

            p_shares = int(tmp_shares[0]["shares"])

            new_shares = b_shares + p_shares
            TOTAL = b_price * new_shares
            TOTAL = format(TOTAL, ".2f")

            db.execute("UPDATE stock_port SET price = :price, shares = :shares, TOTAL = :TOTAL WHERE username = :username AND symbol = :symbol",
                       price=b_price, shares=new_shares, TOTAL=TOTAL, username=username, symbol=symbol)

        # Remember message from session
        session["message"] = "Bought!"

        # Redirect to index.html
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get username from session
    username = session["username"]

    # Get data from history table
    display = db.execute("SELECT symbol, price, shares, transacted FROM history WHERE username = :username ORDER BY id DESC LIMIT 15",
                         username=username)

    # Remember message from session
    session["message"] = "Reistered!"

    # Rendering history.html
    return render_template("history.html", display=display)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]
        session["message"] = "Registered!"

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Redirect to quote.html via get method
    if request.method == "GET":
        return render_template("quote.html")
    else:
        data = lookup(request.form.get("symbol"))

        # If symbol is not available
        if data == None:
            return apology ("must provide correct symbol", 403)
        else:
            return render_template("quoted.html", rows = data)

        session["message"] = "Registered!"

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # Redirect to register.html
    if request.method == "GET":
        return render_template("register.html")

    else:
        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 403)

        # Ensure username was not used
        username_checking = db.execute("SELECT username FROM users WHERE username = :username",
                              username=request.form.get("username"))

        if len(username_checking) != 0:
            return apology("this username is used", 403)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 403)

        # Password checking
        checked = pass_check(password)
        if checked == False:
            return redirect("/register")

        # Ensure password confirmation was submitted
        confirmation = request.form.get("confirmation")
        if not confirmation or confirmation != password:
            return apology("must provide confirmation password", 403)

        # Storing account into database
        h = generate_password_hash(request.form.get("password"), method="pbkdf2:sha256", salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :h)", username=username, h=h)

        # Redirect to index.html
        return redirect("/login")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get username from session
    username = session["username"]

    # User reached route via GET
    if request.method == "GET":

        # Get symbol and shares from stock_port
        display = db.execute("SELECT symbol, shares FROM stock_port WHERE username = :username",
                              username=username)

        return render_template("sell.html", display=display)

    else:

        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 403)

        # Ensure shares was submitted correctly
        shares = request.form.get("shares")
        SharesCheck = shares_check(shares)

        if SharesCheck == False:
            return apology("shares must be in non-decimal number format", 403)

        if not shares or int(shares) < 1:
            return apology("must provide positive number of shares", 403)

        # Ensure this stock is available
        data = lookup(request.form.get("symbol"))

        if data == None:
            return apology("must provide correct symbol", 403)

        # Get available cash from users table
        tmp_cash = db.execute("SELECT cash FROM users WHERE username = :username", username=username)

        # Get available stock's shares from stock_port table
        tmp_re_shares = db.execute("SELECT shares FROM stock_port WHERE username = :username AND symbol = :symbol",
                                username=username, symbol=symbol)

        # Neutralize user's data into key value format
        cash = float(tmp_cash[0]["cash"])
        re_shares = int(tmp_re_shares[0]["shares"])
        s_price = float(data["price"])
        s_shares = int(shares)
        s_h_shares = -1 * s_shares

        # Ensure that remaining shares is enough to sell
        if re_shares < s_shares:
            return apology("your sell is over your remaining shares", 403)

        # Calculate
        sold = s_price * s_shares
        changed = cash + sold

        # Recording sell history
        db.execute("INSERT INTO history (username, symbol, price, shares) VALUES (:username, :symbol, :price, :shares)",
                   username=username, symbol=data["symbol"], price=data["price"], shares=s_h_shares)

        # Update users table
        db.execute("UPDATE users SET cash = :cash WHERE username = :username",
                   cash=changed, username=username)

        # Update current cash
        new_shares = re_shares - s_shares

        # Check if user sell all stock shares
        if new_shares == 0:
            db.execute("DELETE FROM stock_port WHERE username = :username AND symbol = :symbol",
                       username=username, symbol=symbol)

        # If user doesn't sell all stock shares
        else:
            TOTAL = s_price * new_shares
            TOTAL = format(TOTAL, ".2f")

            db.execute("UPDATE stock_port SET price = :price, shares = :shares, TOTAL = :TOTAL WHERE username = :username AND symbol = :symbol",
                       price=s_price, shares=new_shares, TOTAL=TOTAL, username=username, symbol=symbol)

        # Remember message from session
        session["message"] = "Sold!"

        # Redirect to index.html
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
