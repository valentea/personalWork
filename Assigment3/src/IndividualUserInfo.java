import UserList.*;
import User.*;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.OutputStream;
import java.util.List;

@WebServlet("/IndividualUserInfo")
public class IndividualUserInfo extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String returnUsername = request.getParameter("userName");
        List<User> userList = UserList.getInstance().getUsers();


        for(User temp : userList){
            if(temp.getUsername().equals(returnUsername)){
                ObjectMapper mapper = new ObjectMapper();
                response.setContentType("application/json");
                OutputStream output =  response.getOutputStream();
                mapper.writeValue(output, temp);
                output.flush();
            }
        }


    }
}
