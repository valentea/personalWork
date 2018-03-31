<html>
<head>
    <title>LentalLib</title>
    <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script>
        function openPage(pageURL) {
            window.location.href = pageURL;
        }

        $.get('/users', function (data) {
            console.log(data);
        });
        $.post('/autoLogOut');


    </script>

    <style>
        h1 {
            font-size: 60px;
            text-align: center;
            padding-top: 200px;
            margin-bottom: 0px;
        }

        #search, #searchType {
            font-size: 20px;
            text-align: center;
        }

        #homeSearchBar {
            width: 175px;
        }

        #everything {
            position: relative;
            margin: 0 -8px 0 -8px;
            padding: 1px 0 150px;
            border: 0;
            background: yellow;
        }

        #topColor {
            position: relative;
            border: 0;
            margin: -8px -8px 0 -8px;
            background: red;
            padding: 150px 0 0;
        }

        #bottomBar {
            position: relative;
            margin-top: -8px;
            margin-left: -8px;
            margin-right: -8px;
            background: red;
            height: 135px;
            bottom: -8px;
            border: 0;
        }

        #signin, #newaccount {
            position: relative;
            text-align: center;
            width: 200px;
            background: yellow;
            background-image: -webkit-linear-gradient(top, yellow, yellowgreen);
            background-image: -moz-linear-gradient(top, yellow, yellowgreen);
            background-image: -ms-linear-gradient(top, yellow, yellowgreen);
            background-image: -o-linear-gradient(top, yellow, yellowgreen);
            background-image: linear-gradient(to bottom, yellow, yellowgreen);
            -webkit-border-radius: 4px;
            -moz-border-radius: 4px;
            border-radius: 4px;
            font-family: Arial, serif;
            color: #ffffff;
            font-size: 20px;
            padding: 10px 20px 10px 20px;
            text-decoration: none;
        }
        #userButtons{
            text-align: center;
        }
    </style>

</head>
<body>
<div id="topColor"></div>
<div id="everything">
    <h1>LentalLib</h1>
    <form action="bookResults.jsp" name="searchQuery" method="post">
        <div id="search">
            <input type="search" id="homeSearchBar" name="searchBar" placeholder="Find a Good Book to Read!">
            <input type="submit" name="submitSearchHome" value="Search"/>
        </div>
        <div id="searchType">
            <input type="radio" name="searchType" value="intitle" checked="checked"> Title
            <input type="radio" name="searchType" value="isbn"> ISBN
            <br>
            <input type="radio" name="searchType" value="inauthor"> Author
            <input type="radio" name="searchType" value="subject"> Genre
        </div>
    </form>
    <div id="userButtons">
        <br>
        <input type="button" id="signin" value="Sign In" onclick="openPage('signIn.jsp')">
        <br>
        <input type="button" id="newaccount" value="Make New Acount" onclick="openPage('newAccount.jsp')">
    </div>
</div>
<div id="bottomBar"></div>
</body>
</html>