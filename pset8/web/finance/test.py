import os

from cs50 import SQL, get_string
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Test code
x = get_string("Number: ")

checked = False

number = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]

check_lenght = len(x)
check_count = 0

for i in range(check_lenght):
    if x[i] in number:
        check_count = check_count + 1

if check_lenght == check_count:
    checked = True

print(check_lenght)
print(check_count)
print(checked)