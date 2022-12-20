# kalenteri_projekti
This is a simple calendar program where the user can make notes. These notes are
written to 'calendarData.json' file in the program's folder. 

This json file can be uploaded to Google Drive. The target folder is specified
in 'driveFolderId.txt' file and has to be manually set by the user.

However, in order for this feature to work, I'd have to add the email of the new
user as a test user for the program in Google's API. The 'uploadToDrive.exe' 
handles uploading the file. This executable is run on closing the calendar
program if the user chooses so.

Alternatively, if the user wants to create their own client in Google's API,
they can specify the client secrets in 'client_secrets.json' file.

Currently the source code for the executable is not available but I will add it
here early next year.
