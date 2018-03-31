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
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/Search")
public class Search extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        ServletContext context = getServletContext();
        String search = request.getParameter("searchBar");
        String type = request.getParameter("searchObj");
        HttpSession session = request.getSession();
        if(type.equals("book")) {
            String searchType = request.getParameter("searchType");
            request.setAttribute("searchType", searchType);
            request.setAttribute("search", search);
            RequestDispatcher dispatch = context.getRequestDispatcher("/bookResults.jsp");
            dispatch.forward(request, response);
        } else if(type.equals("user")) {
            List<User> userList = UserList.getInstance().getUsers();
            List<User> userResults = new ArrayList<>();
            for (User temp : userList) {
                if ((boolean) session.getAttribute("loggedIn")) {
                    if (temp.getUsername().equals(session.getAttribute("currentUsername"))) {
                        continue;
                    }
                }
                if (search.equals("")) {
                    userResults.add(temp);
                } else if (temp.getUsername().startsWith(search)) {
                    userResults.add(temp);
                }
            }
            ObjectMapper map = new ObjectMapper();
            String resultUsrJson = map.writeValueAsString(userResults);
            request.setAttribute("userResult", resultUsrJson);
            RequestDispatcher dispatch = context.getRequestDispatcher("/UserResults.jsp");
            dispatch.forward(request, response);
        }

    }

}
