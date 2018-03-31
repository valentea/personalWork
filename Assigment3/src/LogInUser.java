import User.*;
import UserList.*;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.List;

@WebServlet("/LogInUser")
public class LogInUser extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        ServletContext context = getServletContext();

        String userName = request.getParameter("Username");
        String password = request.getParameter("Password");


        List<User> userList = UserList.getInstance().getUsers();

        for (User temp : userList) {
            if (temp.getUsername().equals(userName)) {
                if (temp.getPassword().equals(password)) {
                    String pageToForward = "/bookResults.jsp";
                    HttpSession session=request.getSession();
                    session.setAttribute("currentImage", temp.getImageURL());
                    session.setAttribute("currentUsername", temp.getUsername());
                    session.setAttribute("loggedIn", true);

                    session.setAttribute("currentUserObject", temp);
                    RequestDispatcher dispatch = context.getRequestDispatcher(pageToForward);
                    dispatch.forward(request, response);
                    return;
                }
            }
        }
        String failedLogin = "Failed To Login";
        request.setAttribute("message", failedLogin);
        RequestDispatcher dispatch = context.getRequestDispatcher("/signIn.jsp");
        dispatch.forward(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }
}
