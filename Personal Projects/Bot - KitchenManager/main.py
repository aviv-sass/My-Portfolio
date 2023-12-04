from responses import *
from telegram.ext import Application
from conversations import *


# for logging errors to the console
async def error(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    print(f'Update {update} caused error {context.error}')


if __name__ == '__main__':
    print('Starting bot...')
    ItemsDict()
    app = Application.builder().token(TOKEN).build()

    # insert commands and conversations
    app.add_handler(help_handler)
    app.add_handler(delete_kitchen_handler)
    app.add_handler(start_conv_handler)
    app.add_handler(set_inventory_conv_handler)
    app.add_handler(set_base_inventory_conv_handler)
    app.add_handler(inventory_handler)
    app.add_handler(base_inventory_handler)
    app.add_handler(insert_items_base_inventory_conv_handler)
    app.add_handler(insert_items_inventory_conv_handler)
    app.add_handler(remove_items_base_inventory_conv_handler)
    app.add_handler(remove_items_inventory_conv_handler)
    app.add_handler(show_inventory_handler)
    app.add_handler(show_base_inventory_handler)
    app.add_handler(show_grocery_list_handler)
    app.add_handler(MessageHandler(filters.TEXT, handle_message))

    # errors
    app.add_error_handler(error)

    print('Polling...')
    app.run_polling()
