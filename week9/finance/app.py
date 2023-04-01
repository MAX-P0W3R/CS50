import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from passlib.apps import custom_app_context as pwd_context

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Auto-reload templates
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses are not cached
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

# Ensure responses are not cached
@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Homepage while you are logged in
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=session["user_id"])

    # Create a space to save the data
    holdings = []
    all_total = 0

    for row in rows:
        stock = lookup(row["symbol"])
        sum_value = (stock["price"] * row["SUM(shares)"])
        holdings.append({"symbol": stock["symbol"], "name": stock["name"], "shares": row["SUM(shares)"], "price": usd(stock["price"]), "total": usd(sum_value)})
        all_total += stock["price"] * row["SUM(shares)"]

    rows = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])
    cash = rows[0]["cash"]
    all_total += cash

    return render_template("index.html", holdings=holdings, cash=usd(cash), all_total=usd(all_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Must provide symbol")

        elif not request.form.get("shares"):
            return apology("Must provide shares")

        elif int(request.form.get("shares")) < 0:
            return apology("Must provide a valid number of shares")

        if not request.form.get("symbol"):
            return apology("Must provide an existing symbol")

        # Lookup function
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if stock is None:
            return apology("Symbol does not exist")

        # Transaction values
        shares = int(request.form.get("shares"))
        transactionx = shares * stock['price']

        # Check user balance for transaction
        user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        cash = user_cash[0]["cash"]

        # Math the user cash
        updt_cash = cash - transactionx

        if updt_cash < 0:
            return apology("Insufficient funds!")

        # Update user balance
        db.execute("UPDATE users SET cash=:updt_cash WHERE id=:id", updt_cash=updt_cash, id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id,symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=stock['symbol'], shares=shares, price=stock['price'])
        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")

# Display transaction history
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, shares, price, transacted FROM transactions WHERE user_id=:user_id", user_id=session["user_id"])
    for i in range(len(transactions)):
        transactions[i]["price"] = usd(transactions[i]["price"])

    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Must provide valid stock symbol")

        # Use the lookup function
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)

        # Check if stock is valid
        if stock == None:
            return apology("Stock symbol not valid", 400)

        else:
            return render_template("quoted.html", stockSpec = {'name': stock['symbol'], 'price': usd(stock['price'])})

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if not request.form.get("username"):
        return apology("Must provide valid username")

    # Check for password
    elif not request.form.get("password"):
        return apology("Must provide valid password")

    elif not request.form.get("confirmation"):
        return apology("Must provide password confirmation")

    elif request.form.get("password") != request.form.get("confirmation"):
        return apology("Passwords do not match!")
    try:
        new_user = db.execute("INSERT INTO users (username, hash) VALUES (?,?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

    except:
        return apology("Username is already registered")

    session["user_id"] = new_user

    return redirect("/")
else:
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Must provide symbol")

        elif not request.form.get("shares"):
            return apology("Must provide shares")

        elif int(request.form.get("shares")) < 0:
            return apology("Must provide valid number of shares")

        if not request.form.get("symbol"):
            return apology("Must provide an existing symbol")

        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)

        rows = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=session["user_id"])

        # Value of transaction
        shares = int(request.form.get("shares"))
        for row in rows:
            if row["symbol"] == symbol:
                if shares > row["SUM(shares)"]:
                    return apology("ERROR!")

        transaction = shares * stock['price']

        user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        cash = user_cash[0]["cash"]

        updt_cash = cash + transaction

        # Update user account balance
        db.execute("UPDATE users SET cash=:updt_cash WHERE id=:id", updt_cash=updt_cash, id=session["user_id"])

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=stock['symbol'], shares= -1 * shares, price=stock['price'])
        flash("Sold!")
        return redirect("/")

    else:
        rows = db.execute("SELECT symbol FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=session["user_id"])
        return render_template("sell.html", symbols = [row["symbol"]for row in rows])

def errorhandler(e):
    """Handle ERROR"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)

for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

