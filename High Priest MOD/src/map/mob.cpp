//Step 4.5: Enable Skill Usage in AI
//Ensure that the AI can handle skill usage. Modify the AI logic in src/map/monster.cpp or src/map/mob.cpp to enable skill usage for summoned monsters.

void mob_ai_sub_hard(struct mob_data *md, int64 tick) {
    // Ensure the monster can use skills
    if (md->state.skillstate == MSS_FREE && md->mode & MD_CANCAST) {
        if (mob_skill_use(md, tick)) {
            md->state.skillstate = MSS_SKILLCAST;
        }
    }
}
