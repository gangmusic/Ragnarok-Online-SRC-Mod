//Step 4: Update Monster Behavior
//Ensure the summoned monsters follow the caster and teleport if they go off-screen. Modify the unit update functions in src/map/monster.cpp.


// Function prototype
void monster_follow(struct mob_data* md);

// Inside the appropriate unit update function (e.g., unit_timer)
if (md->master_id) {
    struct map_session_data* master_sd = map_id2sd(md->master_id);
    if (master_sd) {
        monster_follow(md);
    }
}

// Implement the follow logic
void monster_follow(struct mob_data* md) {
    struct map_session_data* sd = map_id2sd(md->master_id);
    if (!sd) return;

    int dist = distance(md->bl.x, md->bl.y, sd->bl.x, sd->bl.y);
    if (dist > SCREEN_DISTANCE_LIMIT) {
        // Teleport the monster to the caster
        md->bl.x = sd->bl.x + rand() % 3 - 1;
        md->bl.y = sd->bl.y + rand() % 3 - 1;
        clif_bl_update(&md->bl, &md->bl, UF_CSHIFT | UF_HEALTH | UF_SPEED);
    } else {
        // Normal follow behavior
        md->target_id = sd->bl.id;
        md->state.attack_type = 0;
        md->min_chase = 1;
        md->state.skillstate = MSS_FREE;
    }
}
