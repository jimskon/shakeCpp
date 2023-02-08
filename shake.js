// JavaScript shakespeare Demo
// Jim Skon, Kenyon College, 2021
const port = 5002;
const baseUrl = 'http://192.168.100.174:'+port;

console.log("Start!");
// Add a click event for the search button
document.querySelector("#search-btn").addEventListener("click", (e) => {
    getMatches();
});

// Build output table from list of name data
function resultsTable(data) {
    lines = data['results'];
    
    var table = '<table class="w3-table-all w3-hoverable" border="2"><tr><th>#</th><th>Match</th><tr>';
    lines.forEach(function (line,i) {
	table += "<tr><td>"+i.toString()+"</td><td>"+line+"</td></tr>";
    });
    table += "</table>";

    return table;
}

function processResults(results) {
    document.querySelector('#searchresults').innerHTML = resultsTable(results);
}

function clearResults() {
    document.querySelector('#searchresults').innerHTML = "";
}

function getMatches(){
    console.log("getMatches!");
    var searchStr=document.querySelector('#search').value;
    console.log(searchStr);

    // Ignore short requests
    if (searchStr.length < 2) return;

    // Clear the previous results
    document.querySelector('#searchresults').innerHTML = "";
    fetch(baseUrl+'/shake/'+searchStr, {
	method: 'get'
    })
	.then (response => response.json() )
        .then (data => processResults(data))
	.catch(error => {
	    {alert("Error: Something went wrong:"+error);}
	})
}


