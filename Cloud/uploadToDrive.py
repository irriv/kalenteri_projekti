from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive

gauth = GoogleAuth()
drive = GoogleDrive(gauth)

with open('driveFolderId.txt') as f:
    id = f.readlines()

upload_file_list = ['calendarData.json']
for upload_file in upload_file_list:
	gfile = drive.CreateFile({'parents': [{'id': id}]})
	# Read file and set it as the content of this instance.
	gfile.SetContentFile(upload_file)
	gfile.Upload() # Upload the file.
	