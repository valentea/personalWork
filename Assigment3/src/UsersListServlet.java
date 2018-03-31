import User.*;
import UserList.*;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.core.JsonFactory.*;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/users")
public class UsersListServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session=request.getSession();
        User user = (User) session.getAttribute("currentUserObject");
        if(user != null){
            session.removeAttribute("currentUserObject");
        }
        session.setAttribute("loggedIn", false);
        ServletContext context = getServletContext();

        ArrayList<User> userList = UserList.getInstance().getUsers();

        ObjectMapper mapper = new ObjectMapper();
        response.setContentType("application/json");
        OutputStream output =  response.getOutputStream();
        mapper.writeValue(output, userList);
        output.flush();
    }
}
