import os
import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        response = requests.get(f"https://cloud-sse.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"

def pass_check(password):
    """Checking password"""
    checked = False

    # Character counting
    lenght_count = len(password)

    # Alphabet checking
    letter_count = False

    alphabet = [ "a", "b", "c", "d", "e", "f", "g", "h",
                 "i", "j", "k", "l", "m", "n", "o", "p",
                 "q", "r", "s", "t", "u", "v", "w", "x",
                 "y", "z"]

    for i in range(lenght_count):
        if password[i].lower() in alphabet:
            letter_count = True

    # Number checking
    number_count = False

    number = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]

    for i in range(lenght_count):
        if password[i] in number:
            number_count = True

    # Password must provides at least 6 characters within letters and number
    if lenght_count >= 6 and letter_count == True and number_count == True:
        checked = True
    else:
        checked = False

    return checked

def shares_check(x):
    """Checking shares value must be integer"""
    checked = False

    number = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]

    check_lenght = len(x)
    check_count = 0

    for i in range(check_lenght):
        if x[i] in number:
            check_count = check_count + 1

    if check_lenght == check_count:
        checked = True

    return checked