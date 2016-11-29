using System.Web.Mvc;

namespace WebApplication1.Areas.projects
{
    public class projectsAreaRegistration : AreaRegistration 
    {
        public override string AreaName 
        {
            get 
            {
                return "projects";
            }
        }

        public override void RegisterArea(AreaRegistrationContext context) 
        {
            context.MapRoute(
                "projects_default",
                "projects/{controller}/{action}/{id}",
                new { action = "Index", id = UrlParameter.Optional }
            );
        }
    }
}