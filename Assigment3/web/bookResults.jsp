<%--
  Created by IntelliJ IDEA.
  User: Alex
  Date: 2/9/18
  Time: 1:20 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%--<jsp:useBean id="user" class="User.User" scope="session"/>--%>

<html>
<head>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <title>Results</title>
    <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script>
        var loggedIn = "<%=session.getAttribute("loggedIn")%>";

        function toggleSearch(x) {
                x.classList.toggle("fa-users");
                if(document.getElementById("searchObj").value === "book"){
                    document.getElementById("searchObj").value = "user";
                    document.getElementById("searchType").style.display = "none";
                } else if(document.getElementById("searchObj").value === "user"){
                    document.getElementById("searchObj").value = "book";
                    document.getElementById("searchType").style.display = "block";
                }
        }

        function bookSelection(selfLink, searchType, apiKey) {
            selfLink = selfLink + "?key=" + apiKey;
            window.location = 'singleBook.jsp' + "?selfLink=" + encodeURIComponent(selfLink) + "&searchType=" + searchType;
        }


        function getResults() {
            var apiKey = "AIzaSyDStHLFy1WVsqD-cFajrTzRWLvd73Q_J50"; //made by me
            var xhttp = new XMLHttpRequest();
            var search = "<%=request.getParameter("searchBar")%>";
            console.log(search);
            var searchType = "<%=request.getParameter("searchType")%>";
            if (searchType === "null") {
                searchType = "intitle";
            }
            document.getElementById(searchType).checked = true;
            if (search !== "null") {
                document.getElementById("searchBar").placeholder = search;
                var url = "https://www.googleapis.com/books/v1/volumes?q=" + encodeURI(searchType) + ":" + encodeURI(search) + "&key=" + apiKey + "&maxResults=12";
                console.log(url);
                xhttp.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        var bookList = JSON.parse(this.responseText);
                        console.log(bookList);
                        if (bookList.totalItems === 0) {
                            document.getElementById("noResults").innerHTML = "NO Results!"
                        }
                        var row;
                        for (var i = 0; i < bookList.items.length; i++) {
                            var table = document.getElementById("resultsTable");
                            if (i % 4 === 0) {
                                row = table.insertRow();
                            }
                            var cell = row.insertCell();
                            var book = bookList.items[i];
                            var title = book.volumeInfo.title;
                            var authors;
                            if (book.volumeInfo.hasOwnProperty("authors")) {
                                authors = "BY: " + book.volumeInfo.authors;
                            } else {
                                authors = "Author not specified"
                            }
                            var picture;
                            var pic = document.createElement("img");
                            if (book.volumeInfo.hasOwnProperty("imageLinks")) {
                                picture = book.volumeInfo.imageLinks.thumbnail;
                            } else {
                                pic.setAttribute("class", "notAvailable");
                                picture = "http://sd-filestor-1.s3-eu-west-1.amazonaws.com/d4951237-c9b0-44d2-ab83-edb0c15fd32c/3cdd8434-5b78-427b-b4a1-87dedb145b92/5266ec5b-2668-44a3-a617-e15bc5ec221d.jpg";

                            }
                            var selfLink = book.selfLink;

                            console.log(selfLink + ", " + title);

                            pic.setAttribute("src", picture);
                            pic.setAttribute("data-selfLink", selfLink);
                            pic.addEventListener("click", function () {
                                var selfLink1 = this.getAttribute("data-selfLink");
                                bookSelection(selfLink1, searchType, apiKey);
                            });

                            var cellTitle = document.createTextNode(title);
                            var cellAuthor = document.createTextNode(authors);

                            var cellTable = document.createElement("table");

                            var cellTableRow0 = cellTable.insertRow(0);
                            cellTableRow0.style.textAlign = "center";
                            var cellTableRow0Coll = cellTableRow0.insertCell(0);
                            cellTableRow0Coll.appendChild(pic);
                            cellTableRow0Coll.style.textAlign = "center";

                            var cellTableRow1 = cellTable.insertRow(1);
                            cellTableRow1.style.textAlign = "center";
                            var cellTableRow1Coll = cellTableRow1.insertCell(0);
                            cellTableRow1Coll.appendChild(cellTitle);
                            cellTableRow1Coll.style.fontWeight = "bold";
                            cellTableRow1Coll.style.textAlign = "center";


                            var cellTableRow2 = cellTable.insertRow(2);
                            cellTableRow2.style.textAlign = "center";
                            var cellTableRow2Coll = cellTableRow2.insertCell(0);
                            cellTableRow2Coll.appendChild(cellAuthor);
                            cellTableRow2Coll.style.fontSize = "small";
                            cellTableRow2Coll.style.textAlign = "center";


                            cellTable.style.margin = "auto";
                            cell.appendChild(cellTable);
                            cell.style.width = "350px";
                        }
                    }
                };

                xhttp.open("GET", url, true);
                xhttp.send();
            }
        }

    </script>

    <style>
        #userIcon {
            position: absolute;
            top: 10px;
            right: 30px;

            display: inline-block;
            width: 130px;
            height: 130px;
            border-radius: 50%;

            background: no-repeat center center;
            background-size: cover;
        }

        .notAvailable {
            height: 190px;
            width: 130px;
        }

        .fa {
            font-size: 70px;
            cursor: pointer;
            user-select: none;
        }

        h1 {
            padding: 0;
            border: 0;
            margin: 0 0 0 -8px;
            background: yellow;
            text-align: center;
            height: available;
        }

        div.container {
            margin: -8px -8px 0 -8px;
            background: red;
            top: 0;
            left: 0;
            height: 150px;
        }

        #homeButton {
            position: relative;
            top: 40px;
            left: 15px;
            height: 75px;
            font-size: 50px;
        }

        #searchBar {
            position: absolute;
            top: 40px;
            left: 300px;
            width: 600px;
            height: 75px;
            font-size: 30px;
        }

        #toggleSearch {
            font-family: FontAwsome;
            background-color: transparent;
            border-width: 0;
            position: absolute;
            left: 800px;
            width: 100px;
            height: 100px;
            top: 25px;
        }

        .fa {
            font-size: 70px;
            cursor: pointer;
            user-select: none;
        }

        #searchType {
            position: absolute;
            top: 40px;
            left: 1000px;
            width: 300px;
            height: 100px;
            font-size: 25px;
        }

        #resultsTable {
            position: center;
        }

        #resultsTableContainer {
            position: relative;
            background: yellow;
            margin: 0 -8px 0 -8px;
            border: 0;
            padding: 0;
            height: 550px;
            overflow: auto;
        }

        #bottomBar {
            position: relative;
            margin: 0 -8px 0 -8px;
            background: red;
            padding-bottom: 120px;
        }
    </style>


</head>
<body onload="getResults()">
<div class="container">
    <a href="homePage.jsp" id="homeButton">LentalLib</a>

    <form name="topBarSearch" action="/Search" method="POST">
        <input type="text" id="searchBar" name="searchBar" placeholder="Find a Good Book to Read">
        <input type="hidden" id="searchObj" name="searchObj" value="book">
        <button type="button" id="toggleSearch"><i onclick="toggleSearch(this)" class="fa fa-book"></i></button>
        <div id="searchType">
            <input type="radio" name="searchType" id="intitle" value="intitle"/>Title
            <input type="radio" name="searchType" id="isbn" value="isbn"/>ISBN
            <br/>
            <input type="radio" name="searchType" id="inauthor" value="inauthor"/>Author
            <input type="radio" name="searchType" id="subject" value="subject"/>Genre
        </div>
    </form>
    <%Boolean loggedIn = (Boolean) session.getAttribute("loggedIn");
        if(loggedIn!= null && loggedIn){%>
        <img id="userIcon" src="<%=session.getAttribute("currentImage")%>" onclick="window.location.href = '/userPage.jsp'">
    <%}%>
</div>

<h1 id="noResults"></h1>
<div id="resultsTableContainer">
    <table id="resultsTable">
        <tr>
        </tr>
    </table>
</div>

<div id="bottomBar"></div>
</body>
</html>