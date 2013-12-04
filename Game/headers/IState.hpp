enum IState
        {
            // Loners
            ILWander,
            ILRushPlayer,

            //Swarmers
            ISWander,
            ISSwarmPlayer,
            ISRushPlayer,

            // Flockers
            IFWander,
            IFRushPlayer,
            IFFollowLeader,

            //Leader
            ILeadWander,
            ILeadRushPlayer
        };
