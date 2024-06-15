#include "map/vending.h"
#include "pc.h"
#include "clif.h"
#include "itemdb.h"

int vending_buy(struct map_session_data *sd, int index, int amount)
{
    struct s_vend *s;
    struct map_session_data *vd;
    struct s_vend_item *item;
    int price;

    // Find the vending session data
    vd = map_id2sd(index);
    if (!vd || !vd->state.vending) {
        clif_displaymessage(sd->fd, "The vending shop is not available.");
        return 0;
    }

    s = vd->vend;
    if (!s) {
        clif_displaymessage(sd->fd, "The vending shop is not available.");
        return 0;
    }

    item = &s->items[index];
    price = item->price * amount;

    if (s->currency_type == VEND_CURRENCY_ZENY) {
        if (sd->status.zeny < price) {
            clif_displaymessage(sd->fd, "Not enough Zeny.");
            return 0;
        }
        sd->status.zeny -= price;
    } else if (s->currency_type == VEND_CURRENCY_CASHPOINTS) {
        if (pc_readaccountreg(sd, "#CASHPOINTS") < price) {
            clif_displaymessage(sd->fd, "Not enough Cash Points.");
            return 0;
        }
        pc_setaccountreg(sd, "#CASHPOINTS", pc_readaccountreg(sd, "#CASHPOINTS") - price);
    } else if (s->currency_type == VEND_CURRENCY_ITEM) {
        int item_id = s->currency_item_id;
        if (pc_count_all_items(sd, item_id) < price) {
            clif_displaymessage(sd->fd, "Not enough items.");
            return 0;
        }
        pc_delitem(sd, item_id, price, 0, 0, LOG_TYPE_SCRIPT);
    }

    // Continue with the rest of the vending transaction
    // ...

    return 1;
}
