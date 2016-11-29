using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication1.Areas.projects.Controllers
{
    public class projectsController : Controller
    {
        public ListProjects<Project> projectList = new List<Project> {
            new Project() { id = 1, title = "Project Title 1", description = "This is one of my projects", imageURL = "~/Content/cs.jpg" },
            new Project() { id = 2, title = "Project Title 2", description = "This is one of my projects", imageURL = "~/Content/cs.jpg" },
            new Project() { id = 3, title = "Project Title 3", description = "This is one of my projects", imageURL = "~/Content/cs.jpg" }
        };
        // GET: projects/projects
        public ActionResult Index()
        {
            return View();
        }

        public PartialViewResult ProjectsPartial()
        {
            return PartialView();
        }
    }
}