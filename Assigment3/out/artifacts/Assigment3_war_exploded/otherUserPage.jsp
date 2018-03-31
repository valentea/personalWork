<%@ page import="User.User" %>
<%@ page import="com.fasterxml.jackson.databind.ObjectMapper" %><%--
  Created by IntelliJ IDEA.
  User: Alex
  Date: 2/26/18
  Time: 9:55 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <title>Search User Result</title>
    <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script>
        var loggedIn = "<%=session.getAttribute("loggedIn")%>";


        document.getElementById("Following").click();

        function toggleSearch(x) {
            x.classList.toggle("fa-users");
            if (document.getElementById("searchObj").value === "book") {
                document.getElementById("searchObj").value = "user";
                document.getElementById("searchType").style.display = "none";
            } else if (document.getElementById("searchObj").value === "user") {
                document.getElementById("searchObj").value = "book";
                document.getElementById("searchType").style.display = "block";
            }
        }

        function load() {
            $.ajax({
                url: "/IndividualUserInfo",
                type: 'GET',
                data: {"userName": "<%=request.getParameter("userName")%>"},
                success: function (data) {
                    console.log(data);
                    populateInfo(data);
                }
            });
        }


        function bookSelection(selfLink, searchType, apiKey) {
            selfLink = selfLink + "?key=" + apiKey;
            window.location = 'singleBook.jsp' + "?selfLink=" + encodeURIComponent(selfLink) + "&searchType=" + searchType;
        }


        function openCity(evt, followType) {
            var i, tabContent, tabLinks;
            tabContent = document.getElementsByClassName("tabcontent");
            for (i = 0; i < tabContent.length; i++) {
                tabContent[i].style.display = "none";
            }
            tabLinks = document.getElementsByClassName("tablinks");
            for (i = 0; i < tabLinks.length; i++) {
                tabLinks[i].className = tabLinks[i].className.replace(" active", "");
            }
            document.getElementById(followType).style.display = "block";
            evt.currentTarget.className += " active";
        }

        function populateInfo(jsonData) {
            $("#bigUserIcon").attr("src", jsonData.imageURL);
            $("#name").text(jsonData.username + "'s Favorite Books!");
            populateFavs(jsonData);
            <%
            User user = (User) session.getAttribute("currentUserObject");
            if(user != null){
            %>
            var currentUser = '<%=user.asJson()%>';
            var jsonCurUser = JSON.parse(currentUser);
            for (i = 0; i < jsonData.followers.length; i++) {
                if (jsonData.followers[i] === jsonCurUser.username) {
                    document.getElementById("followButtonText").innerText = "Unfollow";
                } else {
                    document.getElementById("followButtonText").innerText = "Follow";
                }
            }
            <%}else{%>
            document.getElementById("followButtonText").innerText = "Follow";
            <%}%>
            populateTables(jsonData);
        }

        $(document).ready(function () {
            $("#followButton").click(function () {
                <%
                User user1 = (User) session.getAttribute("currentUserObject");
                if(user1 != null){
                %>
                if (document.getElementById("followButtonText").innerText === "Unfollow") {
                    document.getElementById("followButtonText").innerText = "Follow";
                    document.getElementById("followButton").value = "Unfollow";
                } else if (document.getElementById("followButtonText").innerText === "Follow") {
                    document.getElementById("followButtonText").innerText = "Unfollow";
                    document.getElementById("followButton").value = "Follow";
                }
                $.ajax({
                    url: "/FollowEvent",
                    type: 'POST',
                    data: {
                        "followButton": document.getElementById("followButton").value,
                        "username": "<%=request.getParameter("userName")%>"
                    },
                    success: function (data) {
                        load();
                    }
                });
                <%}%>
            });
        });

        function populateTables(currUser) {

            //Populate Following Table
            var row;
            var followingTable = document.getElementById("followingTable");
            $("#followingTable").children().remove();
            console.log(followingTable);
            for (var i = 0; i < currUser.following.length; i++) {
                row = followingTable.insertRow();
                var person = currUser.following[i];
                var cellPerson = document.createTextNode(person);
                row.appendChild(cellPerson);
                row.style.textAlign = "center";
                row.style.width = "350px";
            }
            //Populate Followers Table
            var followersTable = document.getElementById("followersTable");
            $("#followersTable").children().remove();
            console.log(followersTable);
            for (var i = 0; i < currUser.followers.length; i++) {
                row = followersTable.insertRow();
                var person1 = currUser.followers[i];
                var cellPerson1 = document.createTextNode(person1);
                row.appendChild(cellPerson1);
                row.style.textAlign = "center";
                row.style.width = "350px";
            }
        }

        function openFollowTable(evt, followType) {
            var i, tabContent, tabLinks;
            tabContent = document.getElementsByClassName("tabcontent");
            for (i = 0; i < tabContent.length; i++) {
                tabContent[i].style.display = "none";
            }
            tabLinks = document.getElementsByClassName("tablinks");
            for (i = 0; i < tabLinks.length; i++) {
                tabLinks[i].className = tabLinks[i].className.replace(" active", "");
            }
            document.getElementById(followType).style.display = "block";
            evt.currentTarget.className += " active";
        }

        function populateFavs(jsonData) {
            // if (searchType === "null") {
            //     searchType = "intitle";
            // }
            // document.getElementById(searchType).checked = true;
            var searchType = "<%=request.getParameter("searchType")%>";
            if (searchType === "null") {
                searchType = "intitle";
            }
            document.getElementById(searchType).checked = true;
            var apiKey = "AIzaSyDStHLFy1WVsqD-cFajrTzRWLvd73Q_J50"; //made by me
            document.getElementById("searchBar").placeholder = jsonData.username;
            var bookList = jsonData.library.favorite;
            console.log(bookList);
            if (bookList.totalItems === 0) {
                document.getElementById("noResults").innerHTML = "NO Results!"
            }
            var row;
            var colCount = 0;
            var table = document.getElementById("resultsTable");
            $("#resultsTable").children().remove();
            for (var i = 0; i < bookList.length; i++) {
                $.ajax({
                    url: "https://www.googleapis.com/books/v1/volumes?q=intitle:" + encodeURI(bookList[i]) + "&key=" + apiKey + "&maxResults=1",
                    type: 'GET',
                    success: function (bookVol) {
                        console.log(bookVol);
                        var book = bookVol.items[0];
                        console.log(table);
                        if (colCount++ % 4 === 0) {
                            row = table.insertRow();
                        }
                        var cell = row.insertCell();
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
                            bookSelection(selfLink1, "intitle", apiKey);
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
                        cell.style.width = "250px";
                        cell.style.borderWidth = "1px";
                        cell.style.borderColor = "black";

                    }
                });
            }
        }

    </script>


    <style>


        #searchType {
            position: absolute;
            top: 40px;
            left: 1000px;
            width: 300px;
            height: 100px;
            font-size: 25px;
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

        .notAvailable {
            height: 190px;
            width: 130px;
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

        #bigUserIcon {
            position: absolute;

            display: inline-block;
            width: 250px;
            height: 250px;
            border-radius: 50%;

            background: no-repeat center center;
            background-size: cover;
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

        .tab {
            position: absolute;
            top: 370px;
            left: 50px;
            overflow: hidden;
            border: 1px solid #ccc;
            background-color: #f1f1f1;
        }

        .tab button {
            background-color: inherit;
            float: left;
            border: 1px black;
            outline: none;
            cursor: pointer;
            padding: 14px 16px;
            transition: 0.3s;
            font-size: 17px;
        }

        .tab button:hover {
            background-color: #ddd;
        }

        .tab button.active {
            background-color: #ccc;
        }

        .tabcontent {
            position: absolute;
            top: 600px;
            display: none;
            padding: 6px 12px;
            border: 3px solid #ccc;
            border-top: none;
        }

        #name {
            position: relative;
            left: 340px;
            top: 21px;
            font-size: 50px;
            width: fit-content;
            background-color: #ffaa10;

        }

        .content {
            position: relative;
            background: yellow;
            margin: 0 -8px 0 -8px;
            border: 0;
            padding: 0;
            height: 600px;
            overflow: auto;
        }

        #resultsTable {
            background-color: #ffbe0a;
            width: 1000px;
            position: relative;
            left: 340px;
        }

        #bottomBar {
            position: relative;
            margin: 0 -8px 0 -8px;
            background: red;
            padding-bottom: 120px;
        }

        #followButton {
            position: absolute;
            top: 20px;
            left: 1000px;
            height: 40px;
            width: 200px;
        }
    </style>
</head>
<body onload="load()">
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
    <%
        Boolean loggedIn = (Boolean) session.getAttribute("loggedIn");
        if (loggedIn != null && loggedIn) {
    %>
    <img id="userIcon" src="<%=session.getAttribute("currentImage")%>" onclick="window.location.href = '/userPage.jsp'">
    <%}%>
</div>
<div class="content">
    <div id="name"></div>
    <button type="button" id="followButton" value="">
        <span id="followButtonText"></span>
    </button>
    <img id="bigUserIcon" src="">
    <h1 id="noResults"></h1>
    <div id="resultsTableContainer">
        <table id="resultsTable">
            <tr>
            </tr>
        </table>
    </div>

    <div class="followTabs">
        <button class="tablinks" onclick="openFollowTable(event, 'Followers')">Followers</button>
        <button class="tablinks" onclick="openFollowTable(event, 'Following')">Following</button>
    </div>

    <div id="Followers" class="tabcontent">
        <table id="followersTable">
            <tr></tr>
        </table>
    </div>

    <div id="Following" class="tabcontent">
        <table id="followingTable">
            <tr></tr>
        </table>
    </div>
</div>
<div id="bottomBar"></div>


</body>
</html>
