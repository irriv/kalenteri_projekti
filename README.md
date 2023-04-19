# kalenteri_projekti
This is a simple calendar program where the user can make notes. 
These notes are written to 'calendarData.json' file in the program's folder. 
This json file can be uploaded to Google Drive.

The 'uploadToDrive.exe' handles uploading the file. This executable is run on closing the calendar program if the user chooses so.

To use the cloud functionality the user has to:
- Create a project in https://console.cloud.google.com.
- Enable Google Drive API in the project.
- Create an OAuth client ID in the project.
- Specify the client secrets in 'client_secrets.json' file.
- Specify a target folder in the user's Google Drive as an ID in 'driveFolderId.txt' file.
- The folder ID is the last part in a Google Drive folder's url, for example, https://drive.google.com/drive/folders/ID
