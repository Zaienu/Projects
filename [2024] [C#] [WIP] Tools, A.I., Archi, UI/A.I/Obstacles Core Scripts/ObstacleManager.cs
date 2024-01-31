using System.Collections.Generic;
using UnityEngine;

namespace Obstacles_Core_Scripts
{
    public static class ObstacleManager
    {
        private static List<GameObject> obstacles = new List<GameObject>();

        public static List<GameObject> Obstacle_List
        {
            get => obstacles;
            set => obstacles = value;
        }
    }
}
