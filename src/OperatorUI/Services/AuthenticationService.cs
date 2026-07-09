using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OperatorUI.Models;

namespace OperatorUI.Services
{
    public class AuthenticationService
    {
        private readonly List<User> _users = new List<User>
        {
            new User("operator", "operator123", UserRole.Operator),
            new User("technician", "tech123", UserRole.Technician),
            new User("engineer", "eng123", UserRole.Engineer),
            new User("admin", "admin123", UserRole.Admin)
        };

        public User login(string username, string password)
        {
            var user = _users.FirstOrDefault(u => u.Username == username && u.Password == password);
            if (user != null)
            {
                return user;
            }
            else
            {
                throw new UnauthorizedAccessException("Invalid username or password.");
            }
        }
    }
}
