from pickle import GET
from unittest import result
import flask
from flask import request, jsonify
import sqlite3

# initialisation api
app = flask.Flask(__name__)
app.config["DEBUG"] = True

"""
Page d'acceuil de l'api
"""
@app.route('/', methods=['GET'])
def home():
    return '''<h1>Flights database ressource</h1>
<p>A test API for API connected to a database in python</p>'''

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
@app.route('/api/v1/ressources/flights/show/all', methods=['GET'])
def showTableFromDatabase():
    query_params = request.args
    table = query_params.get('table')
    number_of_lines = query_params.get('nbLines')

    req = "SELECT * FROM "

    # liste des tables a changer
    if (table in ["airlines","airports","routes"]):
        # creation de la requete
        req += table
    else :
        return '''<h1>Argument de table non valable</h1>'''
    if number_of_lines:
        req += " LIMIT " + number_of_lines + ";"
    if not(table):
        return page_not_found(404)
    
    # initialisation db
    conn = sqlite3.connect('./database/flights.db', check_same_thread=False)
    
    # execution de la requete SQL
    cursor = conn.cursor()
    cursor.execute(req)

    # recuperation des resultats
    results = cursor.fetchall()

    # fermeture de la base de donnees
    cursor.close()
    conn.close()

    return jsonify(results)

app.run()