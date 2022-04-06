def getHomePage():
    return '''<!DOCTYPE html>
<html lang="fr">
<title>APP Showroom Api</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">

<body>
<div>
  <h1 style=>Zone de tests pour l'API sans MQTT</h1>
  <a href="/api/v1/ressources/flights/show/coordinates">Afficher les coordonées</a>
  <form action="/api/v1/ressources/flights/show/all" method="get">
    <label for="table">Table name:</label><br>
    <input type="text" name="table"><br>
    <input type="submit" value="Show">
  </form>
</div>
</body>
</html>
'''