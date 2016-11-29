using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace WebApplication1.Areas.projects.Models
{
    public class Project
    {
        public int id { set; get; }
        public string title { get; set; }

        public string description { get; set; }

        public string imageURL { get; set; }

        public int year { get; set; }
    }
}