CREATE TABLE projectFile (
[id] integer PRIMARY KEY autoincrement NOT NULL,
[widgetId] INT NOT NULL,
[dirId] integer NOT NULL,
[fileDir] VARCHAR(150) NOT NULL,
[fileName] VARCHAR(80) NOT NULL,
[description] VARCHAR(100),
CONSTRAINT fk_widget FOREIGN KEY([widgetId]) REFERENCES [widget]([id]),
CONSTRAINT fk_project_dir FOREIGN KEY([dirId]) REFERENCES [projectDir]([id]));