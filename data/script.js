

// Requête HTTP Asynchrone: Retour valeur Temperature
function temperatureButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200)
            document.getElementById("valeurTemperature").innerHTML = this.responseText;
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourtemperature", true);
    xhttp.send();
}

// Requête HTTP Asynchrone: Retour valeur Humidity
function humidityButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200)
            document.getElementById("valeurHumidity").innerHTML = this.responseText;
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourhumidity", true);
    xhttp.send();
}

// Requête HTTP Asynchrone: Retour valeur Gaz
function gazButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200)
            document.getElementById("valeurGaz").innerHTML = this.responseText;
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourgaz", true);
    xhttp.send();
}

// Requête HTTP Asynchrone: Retour valeur Pression
function pressionButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200)
            document.getElementById("valeurPression").innerHTML = this.responseText;
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourpression", true);
    xhttp.send();
}

// Requête HTTP Asynchrone: Prise de la photo
function photo() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200) {
            var timestamp = new Date().getTime();     
            var el = document.getElementById("photo");     
            el.src = "./photo.jpg?t=" + timestamp;   
        }
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourphoto", true);
    xhttp.send();
}

/*
// Création et envoi d'une requête HTTP Asynchrone vers notre serveur ESP sur le chemin "/ledon"
function onButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "ledon", true);
    xhttp.send();
}

// Création et envoi d'une requête HTTP Asynchrone vers notre serveur ESP sur le chemin "/ledon"
function offButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "ledoff", true);
    xhttp.send();
}
*/

/*  Toutes les 2 sec (2000 ms)
    Création/Envoi de la requete GET sur le chemin "/retourtemperature"
    Retourne la valeur sur le SPAN de la page HTML
*/
/*
setInterval(function getData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200)
            document.getElementById("valeurTemperature").innerHTML = this.responseText;
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourtemperature", true);
    xhttp.send();
}
, 2000);
*/

/*  Toutes les 10 sec
    Création/Envoi de la requete GET sur le chemin "/retourhumidity"
    Retourne la valeur sur le SPAN de la page HTML
*/
/*
setInterval(function getData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        // 4 = requete prête et status 200 = OK
        if(this.readyState == 4 && this.status == 200)
            document.getElementById("valeurHumidity").innerHTML = this.responseText;
    }; // ne pas oublier le ;

    xhttp.open("GET", "retourhumidity", true);
    xhttp.send();
}
, 10000);
*/