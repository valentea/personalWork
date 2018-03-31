import User.User;
import UserList.UserList;
import com.sun.codemodel.internal.util.UnicodeEscapeWriter;

import javax.jws.soap.SOAPBinding;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/AddLib")
public class AddLib extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String type = request.getParameter("type");
        String title = request.getParameter("title");
        HttpSession session = request.getSession();
        User currentUser = (User) session.getAttribute("currentUserObject");
        UserList userList = UserList.getInstance();
        boolean inLib = false;
        for(String fave : currentUser.getLibrary().getFavorite()){
            if(fave.equals(title)){
                inLib = true;
            }
        }
        for(String read : currentUser.getLibrary().getRead()){
            if(read.equals(title)){
                inLib = true;
            }
        }
        if(!inLib) {
            userList.addATitle(currentUser, title, type);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }
}
