from commands import *
from settings import *
from telegram.ext import CommandHandler, MessageHandler, ConversationHandler, filters

# init conversations handler
start_conv_handler = ConversationHandler(
    entry_points=[CommandHandler("start", start_command)],
    states={
        INIT_NAME_EXECUTE: [MessageHandler(filters.TEXT and (~ filters.COMMAND), init_name_execute)],
        INIT_PASSCODE_EXECUTE: [MessageHandler(filters.TEXT and (~ filters.COMMAND), init_passcode_execute)],
        INIT_BASE_INVENTORY_EXECUTE: [
            MessageHandler(filters.TEXT and (~ filters.COMMAND), init_base_inventory_execute)],
        INIT_INVENTORY_EXECUTE: [MessageHandler(filters.TEXT and (~ filters.COMMAND), init_inventory_execute)]
    },
    fallbacks=[CommandHandler(["cancel"], cancel_init_command)],
)

set_inventory_conv_handler = ConversationHandler(
    entry_points=[CommandHandler("setInventory", set_inventory)],
    states={
        INIT_INVENTORY_EXECUTE: [MessageHandler(filters.TEXT and (~ filters.COMMAND), init_inventory_execute)]
    },
    fallbacks=[CommandHandler(["cancel"], silent_cancel_command)],
)

set_base_inventory_conv_handler = ConversationHandler(
    entry_points=[CommandHandler("setBaseInventory", set_base_inventory)],
    states={
        INIT_BASE_INVENTORY_EXECUTE: [MessageHandler(filters.TEXT and (~ filters.COMMAND), init_base_inventory_execute)]
    },
    fallbacks=[CommandHandler(["cancel"], silent_cancel_command)],
)

insert_items_base_inventory_conv_handler = ConversationHandler(
    entry_points=[CommandHandler("insertItemsBaseInventory", insert_items_base_inventory)],
    states={
        INSERT_ITEMS_BASE_INVENTORY_EXECUTE: [MessageHandler(filters.TEXT and (~ filters.COMMAND),
                                                             insert_items_base_inventory_execute)]
    },
    fallbacks=[CommandHandler(["cancel"], silent_cancel_command)],
)

insert_items_inventory_conv_handler = ConversationHandler(
    entry_points=[CommandHandler("insertItemsInventory", insert_items_inventory)],
    states={
        INSERT_ITEMS_INVENTORY_EXECUTE: [
            MessageHandler(filters.TEXT and (~ filters.COMMAND), insert_items_inventory_execute)]
    },
    fallbacks=[CommandHandler(["cancel"], silent_cancel_command)],
)

remove_items_base_inventory_conv_handler = ConversationHandler(
    entry_points=[CommandHandler("removeItemsBaseInventory", remove_items_base_inventory)],
    states={
        REMOVE_ITEMS_BASE_INVENTORY_EXECUTE: [MessageHandler(filters.TEXT and (~ filters.COMMAND),
                                                             remove_items_base_inventory_execute)]
    },
    fallbacks=[CommandHandler(["cancel"], silent_cancel_command)],
)

remove_items_inventory_conv_handler = ConversationHandler(
    entry_points=[CommandHandler("removeItemsInventory", remove_items_inventory)],
    states={
        REMOVE_ITEMS_INVENTORY_EXECUTE: [
            MessageHandler(filters.TEXT and (~ filters.COMMAND), remove_items_inventory_execute)]
    },
    fallbacks=[CommandHandler(["cancel"], silent_cancel_command)],
)
