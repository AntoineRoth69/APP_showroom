from pickle import GET
from unittest import result
import flask
from flask import request, jsonify
import sqlite3
import matplotlib.pyplot as plt
import index

# initialisation api
app = flask.Flask(__name__)
app.config["DEBUG"] = True

"""
Page d'acceuil de l'api
"""
@app.route('/', methods=['GET'])
def home():
    return index.getHomePage()

"""
Page d'erreur de l'api
"""
@app.errorhandler(404)
def page_not_found(e):
    return "<h1>404</h1><p>The resource could not be found.</p>", 404

"""
@app_url/api/v1/ressources/flights/show/all?table=str[&nbLines=int]
Retourne toutes les lignes d'une table donnees dans la requete.
Renvoie a la page d'erreur en cas de table non existante
Pour limiter le nombre de lignes, renseigner nbLines
"""
# a faire evoluer pour assurer le fonctionnement
# avec les champs des tables
@app.route('/api/v1/ressources/flights/show/all', methods=['GET'])
def showTableFromDatabase():
    # initialisation db
    conn = sqlite3.connect('./database/flights.db', check_same_thread=False)
    
    # requete SQL contenant toutes les tables de la base de données
    cursor = conn.cursor()
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
    tables = cursor.fetchall()

    tableChoice = []
    for t in tables:
        tableChoice.append(t[0])

    query_params = request.args
    table = query_params.get('table')
    number_of_lines = query_params.get('nbLines')

    req = "SELECT * FROM "

    # liste des tables a changer
    if (table in tableChoice):
        # creation de la requete
        req += table
    else :
        return '''<h1>Argument de table non valable</h1>'''
    if number_of_lines:
        req += " LIMIT " + number_of_lines + ";"
    if not(table):
        return page_not_found(404)
    
    cursor.execute(req)

    # recuperation des resultats
    results = cursor.fetchall()

    # fermeture de la base de donnees
    cursor.close()
    conn.close()

    return jsonify(results)

@app.route('/api/v1/ressources/flights/show/coordinates', methods=['GET'])
def trace_airports():
    # initialisation db
    conn = sqlite3.connect('./database/flights.db', check_same_thread=False)
    
    # execution de la requete SQL
    cursor = conn.cursor()
    cursor.execute("""
        SELECT CAST(longitude AS float),
        CAST(latitude AS float)
        FROM airports;
        """)

    # recuperation des resultats
    results = cursor.fetchall()

    # fermeture de la base de donnees
    cursor.close()
    conn.close()

    return jsonify(results)

app.run()