from typing import Final

TOKEN: Final = 'insert token here'
BOT_USERNAME: Final = '@KitchenManagerBot'

replies = {
    'start': 'היי! אני מנהל המטבח שלך.\n'
             'אוכל לעזור לך לנהל את המלאי שלך ולספק עברוך מגוון שירותים, בהתאם למה שתגדיר.\n'
             'שנתחיל לעבוד? זה יקח כמה דקות.\nבכל שלב תוכל לבטל את ההגדרות על ידי לחיצה על cancel.',
    'help': 'אתה יכול לבקש ממני: \n * לספק רשימת קניות עבורך. \n'
            ' * לעדכן את המלאי הבסיסי שחייב להיות לך במטבח. '
            '\n * לעדכן את המלאי שלך. \n * .לעדכן את רשימת הקניות שלך '
            '\n אל תהסס לשאול אותי כל דבר!',
    'bucketPatternGuide': 'הכנס כך:\nכמות1 פריט1 \nכמות2 פריט2\nוכך הלאה...\nאין לכתוב פריט יותר מפעם אחת.'
                          '\nקלט של *ריקה* - לא יכניס דבר.\n',
    'setName': 'הגדר שם למטבח שלך.\nשים לב, השם חייב להיות באורך 4 תווים לפחות, אותיות ומספרים בלבד וללא רווחים.\n',
    'setPasscode': 'הגדר קוד בין ארבע ספרות.\n',
    'invalidPasscode': 'הקוד שהזנת אינו תקין. נסה שוב. הקוד חייב להיות בין ארבע ספרות.\n',
    'setBaseInventory': 'הגדר מלאי מזון בסיסי שתמיד חייב להיות אצלך בבית, ',
    'invalidInput': 'הקלט שהזנת אינו תקין. נסה שוב.\n',
    'setInventory': 'הגדר את מלאי המזון הנוכחי אצלך בבית, ',
    'actionComplete': 'הפעולה הושלמה בהצלחה!\n',
    'cancel': 'הפעולה בוטלה. תודה.\n',
    'kitchenExist': 'הקמנו מטבח עבורך בעבר.\n',
    'showInventory': 'מלאי המטבח שלך הוא:\n',
    'showBaseInventory': 'מלאי המטבח הבסיסי שהגדרת הוא:\n',
    'showGroceryList': 'רשימת הקניות שלך היא:\n',
    'boringMessage': 'כתוב משהו... או /help כדי לקבל עזרה.\n',
    'insertItemsBaseInventory': 'הוסף פריטים למלאי הבסיסי שלך, ',
    'insertItemsInventory': 'הוסף פריטים למלאי הנוכחי שלך, ',
    'wantToSetupFromScratch': 'האם אתה רוצה להגדיר מטבח חדש?\nפעולה זו תמחק את כל ההגדרות הקודמות שלך.'
                              '\nלחץ על /deleteKitchen כדי למחוק את המטבח שלך.\n',
    'deleteKitchen': 'המטבח שלך נמחק בהצלחה!\nכדי להתחיל מחדש לחץ על /start.\n',
    'removeItemsInventory': 'הסר פריטים מהמלאי הנוכחי שלך, ',
    'removeItemsBaseInventory': 'הסר פריטים מהמלאי הבסיסי שלך, ',
    'aboutCancel': 'ניתן לבטל את הפעולה ידי לחיצה על /cancel.\n',
}

# Init states
(SETUP_COMMAND, INIT_NAME_EXECUTE, INIT_PASSCODE_EXECUTE, INIT_BASE_INVENTORY_EXECUTE, INIT_INVENTORY_EXECUTE,
 INSERT_ITEMS_BASE_INVENTORY_EXECUTE, INSERT_ITEMS_INVENTORY_EXECUTE, INSERT_ITEMS_GROCERY_LIST_EXECUTE,
 REMOVE_ITEMS_BASE_INVENTORY_EXECUTE, REMOVE_ITEMS_INVENTORY_EXECUTE, REMOVE_ITEMS_GROCERY_LIST_EXECUTE) = range(11)

casual_commands = ['/help', '/showBaseInventory', '/showInventory', '/showGroceryList', '/insertItemsBaseInventory',
                   '/insertItemsInventory', '/removeItemsBaseInventory', '/removeItemsInventory']
