<%--
  Created by IntelliJ IDEA.
  User: Alex
  Date: 2/9/18
  Time: 2:59 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>SingleBook</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>

    <script>

        document.getElementById("defaultOpenBook").click();
        document.getElementById("defaultFollowing").click();

        function favBook() {
            $.ajax({
                url: "/AddLib",
                type: 'POST',
                data:{
                    "title": document.getElementById("bookInfoTable").getAttribute("data-title"),
                    "type": "favorite"
                },
                success:function (data) {
                }
            });
        }

        function readBook() {
            $.ajax({
                url: "/AddLib",
                type: 'POST',
                data:{
                    "title": document.getElementById("bookInfoTable").getAttribute("data-title"),
                    "type": "read"
                },
                success:function (data) {
                }
            })
        }

        var loggedIn = "<%=session.getAttribute("loggedIn")%>";
        if(loggedIn === "false"){
            $("#userIcon").remove();
        }
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
        function setPageEllements() {
            var selfLink = "<%=request.getParameter("selfLink")%>";
            var searchType = "<%=request.getParameter("searchType")%>";
            document.getElementById(searchType).checked = true;
            var xhttp = new XMLHttpRequest();
            var url = selfLink;
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var book = JSON.parse(this.responseText);
                    console.log(book);
                    var rating;

                    var ratingTable = document.getElementById("bookRating");
                    var row = ratingTable.insertRow(0);
                    var ratingLable = row.insertCell();
                    ratingLable.innerHTML = "Rating:";
                    if(book.volumeInfo.hasOwnProperty("averageRating")){
                        rating = book.volumeInfo.averageRating;
                        for(var i=1; i<=5;i++){
                            var ratingCell = row.insertCell();
                            if(i <= rating) {
                                ratingCell.innerHTML = "<i class=\"fa fa-star\" aria-hidden=\"true\"></i>";
                            }else if(i>rating && (i-rating)>=.3 &&  (i-rating)<=.7){
                                ratingCell.innerHTML = "<i class=\"fa fa-star-half-o\" aria-hidden=\"true\"></i>";
                            }else{
                                    ratingCell.innerHTML = "<i class=\"fa fa-star-o\" aria-hidden=\"true\"></i>"
                            }

                            row.appendChild(ratingCell);
                        }
                    }else {
                        var errorCell = row.insertCell(0);
                        var eRating = document.createTextNode("No rating avalable");
                        errorCell.appendChild(eRating);
                        row.appendChild(errorCell);
                    }


                    var picSrc;
                    if(book.volumeInfo.hasOwnProperty("imageLinks")){
                        if(book.volumeInfo.imageLinks.hasOwnProperty("large")) {
                            picSrc = book.volumeInfo.imageLinks.large;
                        }else if(book.volumeInfo.imageLinks.hasOwnProperty("thumbnail")){
                            picSrc = book.volumeInfo.imageLinks.thumbnail;
                        }else{
                            picSrc = "http://sd-filestor-1.s3-eu-west-1.amazonaws.com/d4951237-c9b0-44d2-ab83-edb0c15fd32c/3cdd8434-5b78-427b-b4a1-87dedb145b92/5266ec5b-2668-44a3-a617-e15bc5ec221d.jpg";
                        }
                    }else{
                        picSrc = "http://sd-filestor-1.s3-eu-west-1.amazonaws.com/d4951237-c9b0-44d2-ab83-edb0c15fd32c/3cdd8434-5b78-427b-b4a1-87dedb145b92/5266ec5b-2668-44a3-a617-e15bc5ec221d.jpg";
                    }
                    var title = book.volumeInfo.title;
                    document.getElementById("searchBar").placeholder = title;
                    var author;
                    if (book.volumeInfo.hasOwnProperty("authors")) {
                        author = "BY: " + book.volumeInfo.authors;
                    } else {
                        author = "Author not specified"
                    }
                    var discription;
                    if (book.volumeInfo.hasOwnProperty("description")) {
                        discription = book.volumeInfo.description;
                    } else {
                        discription = "No given description"
                    }
                    var publisher;
                    if (book.volumeInfo.hasOwnProperty("publisher")) {
                        publisher = "Publisher: " + book.volumeInfo.publisher;
                    } else {
                        publisher = "Publisher not specified"
                    }

                    var table = document.getElementById("bookInfoTable");
                    table.setAttribute("data-title", title);

                    var row0 = table.insertRow(0);
                    var tCell = row0.insertCell(0);
                    tCell.setAttribute("class", "title");
                    var tTitle = document.createTextNode(title);
                    tCell.appendChild(tTitle);
                    row0.appendChild(tCell);

                    var row1 = table.insertRow(1);
                    var aCell = row1.insertCell(0);
                    var tAuthor = document.createTextNode(author);
                    aCell.appendChild(tAuthor);
                    aCell.style.fontSize = "50px";
                    row1.appendChild(aCell);

                    var row2 = table.insertRow(2);
                    var pCell = row2.insertCell(0);
                    var tPublisher = document.createTextNode(publisher);
                    pCell.appendChild(tPublisher);
                    pCell.style.fontSize = "30px";
                    row2.appendChild(pCell);

                    var row3 = table.insertRow(3);
                    var dhtCell = row3.insertCell(0);
                    var discriptionHardText = document.createTextNode("Description:");
                    dhtCell.appendChild(discriptionHardText);
                    dhtCell.style.fontSize = "30px";
                    row3.appendChild(dhtCell);

                    var row4 = table.insertRow(4);
                    var dCell = row4.insertCell(0);
                    dCell.innerHTML = discription;
                    dCell.style.fontSize = "20px";
                    dCell.style.fontFamily = "\"Courier New\", Courier, monospace";
                    row4.appendChild(dCell);


                    document.getElementById("bookCover").setAttribute("src", picSrc);


                }
            };
            xhttp.open("GET", url, true);
            xhttp.send();
        }
    </script>
    <style>
        div.container {
            position: relative;
            background: red;
            height: 150px;
            margin: -8px -8px -8px -8px;
        }

        div.content {
            position: relative;
            background: yellow;
            height: 1000px;
            margin-bottom: 0;
            padding-bottom: 0;
            border-bottom:0;
            margin-left: -8px;
            margin-right: -8px;
            bottom: -8px;
            overflow: auto;
        }

        #bottomBar {
            position: relative;
            margin-left: -8px;
            margin-right: -8px;
            bottom: -8px;
            padding-bottom:100px;
            background: red;
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

        #searchType {
            position: absolute;
            top: 40px;
            left: 1000px;
            width: 300px;
            height: 100px;
            font-size: 25px;
        }

        .fa {
            font-size: 50px;
            cursor: pointer;
            user-select: none;
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

        #submit {
            position: absolute;
            left: 800px;
            width: 100px;
            top: 90px;
        }

        #searchType {
            position: absolute;
            top: 40px;
            left: 1000px;
            width: 300px;
            height: 100px;
            font-size: 25px;
        }

        #bookPic {
            position: absolute;
            top: 20px;
            left: 20px;
        }

        #bookInfoTable {
            position: absolute;
            top: 20px;
            left: 500px;
            height: 120px;
            width: 850px;
            overflow: auto;
        }
        .title {
            font-size: 60px;
            font-weight: bold;
        }

        #bookRating{
            position: relative;
            top: 625px;
            left: 70px;
            font-size: xx-large;
        }

        .dropbtn {
            position: center;
            width: 200px;
            background-color: #ff9c20;
            color: white;
            padding: 16px;
            font-size: 16px;
            border: none;
        }

        .dropdown {
            position: relative;
            top: 630px;
            left: 50px;
            width: 200px;
            background-color: #ffaa10;
            display: inline-block;
        }

        .dropdown-content {
            display: none;
            position: absolute;
            background-color: #ffaa10;
            width: 200px;
        }

        .dropdown:hover .dropdown-content {
            display: block;
        }

        .dropdown:hover .dropbtn {
            background-color: #ff9c20;
        }

        #favoriteBook, #readBook{
            border: 0;
            font-family: Arial;
            color: #ffffff;
            font-size: 20px;
            background: #ffaa10;
            padding: 10px 20px 10px 20px;
            text-decoration: none;
        }

        #favoriteBook:hover, #readBook:hover{
            background: #ff9c20;
            text-decoration: none;
        }

    </style>
</head>
<body onload=setPageEllements()>
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
<div class="content">
    <div id="bookPic">
        <img id="bookCover" height="600px" width="400px">
    </div>
    <table id="bookRating">
        <tr></tr>
    </table>

    <div class="dropdown">
        <button class="dropbtn">Add to Library</button>
        <div class="dropdown-content">
            <button id="favoriteBook" onclick="favBook()">Favorites</button>
            <br>
            <button id="readBook" onclick="readBook()">Read</button>
        </div>
    </div>
    <table id="bookInfoTable">
        <tr></tr>
    </table>
</div>
<div id="bottomBar"></div>


</body>
</html>
