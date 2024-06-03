//find the function skill_castend_pos. Add the logic for creating the clone. You need to add the skill ID in the switch case structure.

case ASC_HALLUCINATIONCLONE:
    if (sd) {
        // Create clone
        struct block_list *bl = map->id2bl(sd->status.char_id);
        struct mob_data *md = mob_once_spawn(bl->m, bl->x, bl->y, "--ja--", MOBID_HALLUCINATIONCLONE, "", "");
        
        if (md) {
            md->status.base_level = sd->status.base_level;
            md->status.job_level = sd->status.job_level;
            md->status.str = sd->status.str;
            md->status.agi = sd->status.agi;
            md->status.vit = sd->status.vit;
            md->status.int_ = sd->status.int_;
            md->status.dex = sd->status.dex;
            md->status.luk = sd->status.luk;
            md->status.hp = sd->status.hp;
            md->status.max_hp = sd->status.max_hp;
            md->status.sp = sd->status.sp;
            md->status.max_sp = sd->status.max_sp;
            md->status.attack = sd->status.attack;
            md->status.def = sd->status.def;
            md->status.mdef = sd->status.mdef;
            md->status.hit = sd->status.hit;
            md->status.flee = sd->status.flee;
            
            // Clone behavior to defend the caster
            md->state.skill_attack = 1;
            md->master_id = sd->status.char_id;
            md->mode = MD_CANATTACK | MD_CANMOVE | MD_CLONE;
            
            // Link clone to the caster
            sd->status.pet_id = md->bl.id;
            
            // Visual effect
            clif->specialeffect(&md->bl, 234, AREA);
        }
    }
    break;
