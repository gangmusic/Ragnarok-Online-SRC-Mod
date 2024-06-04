//Step 2: Implement the Skill Script
//Edit skill_castend_nodamage_id in src/map/skill.cpp to add the functionality for summoning the appropriate monsters.

// Function prototype
void summon_monster(struct map_session_data* sd, int class_, int duration);

// Inside the skill_castend_nodamage_id function
case PR_AUTOATTACKSUMMON: {
    int level = skill_lv;
    int monster_class;
    int summon_count = 3; // Maximum number of summoned monsters

    // Define the monster class based on the skill level
    switch (level) {
        case 1:
            monster_class = MOBID_HIGH_PRIEST;
            break;
        case 2:
            monster_class = MOBID_SNIPER;
            break;
        case 3:
            monster_class = MOBID_LORD_KNIGHT;
            break;
        default:
            return 0;
    }

    // Summon the monsters
    for (int i = 0; i < summon_count; ++i) {
        summon_monster(sd, monster_class, skill_db[skill_id].duration1);
    }

    break;
}
