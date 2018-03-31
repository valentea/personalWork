
<html>
<head>
    <title>Log In</title>
    <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script>
        $("#idForm").submit(function() {
            $.ajax({
                type: "POST",
                url: "/LogInUser",
                data: $("#idForm").serialize()
            });
        });
    </script>
</head>
<style>

    #LogIn{
        font-size: 70px;
        position: center;
        position: relative;
        top: 300px;
        text-align: center;
    }

    #urn{
        position: center;
        position: relative;
        top: 300px;
        text-align: center;
    }

    #submit {
        border-radius: 28px;
        font-family: Arial;
        color: #ffffff;
        font-size: 20px;
        background: #3498db;
        padding: 10px 20px 10px 20px;
        text-decoration: none;
    }

    #submit:hover {
        background: #3cb0fd;
        text-decoration: none;
    }

    .bottomBar {
        position: relative;
        margin-left: -8px;
        margin-right: -8px;
        bottom: -8px;

        padding-bottom:100px;
        background: red;
    }

    .content{
        position: relative;
        margin-left: -8px;
        margin-right: -8px;
        background-color: yellow;
        height: 600px;
        top:-55px;
    }

    .container{
        position: relative;
        margin-left: -8px;
        margin-right: -8px;
        top: -8px;
        padding-top:100px;
        background: red;
    }

    #homeButton {
        position: relative;
        top: -50px;
        left: 15px;
        height: 75px;
        font-size: 50px;
    }

</style>
<body>
<div class="container">
    <a href="homePage.jsp" id="homeButton">LentalLib</a>
</div>

<div class="content">
    <h1 id="LogIn">LOG IN</h1>

    <form class="login" action="/LogInUser" method="post">
        <div id="urn">Username<br>
            <input type="text" name="Username" id="username"></input><br>
            Password<br>
            <input type="text" name="Password" id="password"></input><br>
            <input id="submit" type="submit" value="Sign In">
        </div>
    </form>
</div>
<div class="bottomBar">
</div>


</body>
</html>

