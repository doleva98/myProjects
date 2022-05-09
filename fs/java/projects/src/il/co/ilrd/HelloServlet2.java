// import java.io.*;
// import javax.servlet.*;
// import javax.servlet.http.*;

// public class HelloServlet2 extends HttpServlet {
// public void doGet(HttpServletRequest req, HttpServletResponse res)
// throws ServletException, IOException {
// res.setContentType("text/html");
// String name = req.getParameter("name");
// PrintWriter out = res.getWriter();
// out.println("<html><body>");
// if (name != null) {
// out.println("<p>Hello </p>" + name);
// out.println("</body></html>");
// out.close();
// } else {
// out.println("<p>Hello World! </p>");
// out.println("</body></html>");
// out.close();
// }

// }
// }