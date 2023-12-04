from commands import *
from settings import *


def handle_response(text: str) -> str:
    if 'שלום' in text:
        return 'שלום וברכה!'
    if 'מה שלומך' in text:
        return 'אני מעולה! מה שלומך?'
    if ('מעולה' or 'טוב' or 'מצוין') in text:
        return 'נהדר!'
    return 'מצטער, אני לא מבין אותך. אנא נסה שוב.'


async def handle_message(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    message_type: str = update.message.chat.type  # either private or group
    text: str = update.message.text  # the message
    # print('User ({update.message.chat.id}) in {message_type}: "{text}"')

    # if the message is in a group and the bot is mentioned
    if message_type == 'group':
        if BOT_USERNAME in text:
            new_text = text.replace(BOT_USERNAME, '').strip()  # remove the bot's username from the message
            response: str = handle_response(new_text)  # process the message
        else:
            return
    else:
        response: str = handle_response(text)
    await update.message.reply_text(response)
