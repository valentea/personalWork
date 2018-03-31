<%--
  Created by IntelliJ IDEA.
  User: Alex
  Date: 2/15/18
  Time: 10:09 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Sign Up</title>
    <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script>
        // function validateAndCreate() {
        //     $.ajax({
        //         url : '/CreateNewUser',
        //         type : 'GET',
        //         data : {
        //             "newUsername" : document.constructNewUser.newUsername.value,
        //             "newPassword" : document.constructNewUser.newPassword.value,
        //             "newImageURL" : document.constructNewUser.newImageURL.value
        //         },
        //         success : function (data) {
        //             alert("got HERE");
        //             alert(data);
        //         }
        //     });
        // }

        $(document).ready(function () {
            $("#constructNewUser").submit(function (e) {
                $.ajax({
                    url: '/CreateNewUser',
                    type: 'GET',
                    data: {
                        "newUsername": document.constructNewUser.newUsername.value,
                        "newPassword": document.constructNewUser.newPassword.value,
                        "newImageURL": document.constructNewUser.newImageURL.value
                    },
                    success: function (data) {
                        var emptyField = "Entry Cannot Be Empty";
                        if (data.valid) {
                            if(data.usernameBool){
                                $("#usrError").html(emptyField);
                            }else if(data.usernameTakenBool){
                                $("#usrError").html("Username Taken")
                            }else if(!data.usernameBool){
                                $("#usrError").html("");
                            }
                            if(data.passwordBool){
                                $("#pswError").html(emptyField);
                            }else if(!data.passwordBool){
                                $("#pswError").html("");

                            }
                            if(data.imageURLBool){
                                $("#imgError").html(emptyField);
                            }else if(!data.imageURLBool){
                                $("#imgError").html("");
                            }
                        }else{
                            window.location = 'bookResults.jsp';
                        }
                    }
                });
                e.preventDefault();
            });
        });
    </script>
</head>
<style>

    #constructNewUser{
        font-size: 30px;
        position: center;
        position: relative;
        top: 150;
        text-align: center;
    }

    #urn{
        position: center;
        position: relative;
        top: 300;
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
        top:-55;
    }

    .container{
        position: relative;
        margin-left: -8px;
        margin-right: -8px;
        top: -8px;
        padding-top:100px;
        background: red;
    }

    h1{
        position: center;
    }

    #usrError, #pswError, #imgError{
        color: red;
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
    <h1>LOG IN!!!</h1>
<form name="constructNewUser" id="constructNewUser">
    User Name
    <input type="text" id="newUsername"> <div id="usrError"></div> <br>
    Password
    <input type="text" id="newPassword"> <div id="pswError"></div> <br>
    Image URL
    <input type="text" id="newImageURL"> <div id="imgError"></div> <br>
    <input type="submit" id="submit">
</div>

<div class="bottomBar"></div>

</form>
</body>
</html>
