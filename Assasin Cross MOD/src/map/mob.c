if (md->mode & MD_CLONE) {
    // Define clone behavior
    if (md->master_id) {
        struct block_list *mbl = map->id2bl(md->master_id);
        if (mbl) {
            // Move towards the master
            unit->walktoxy(&md->bl, mbl->x, mbl->y, 1);
            // Attack any enemy that attacks the master
            struct block_list *target = battle->get_enemy(mbl, mbl->x, mbl->y, md->bl.m, battle_config.enemy_mob);
            if (target) {
                md->target_id = target->id;
                mob->target(&md->bl, target->id, 1);
            }
        }
    }
}
