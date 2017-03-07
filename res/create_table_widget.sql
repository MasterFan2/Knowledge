CREATE TABLE widget (
[id] integer PRIMARY KEY autoincrement NOT NULL,
[name] VARCHAR(100) NOT NULL,
[className] VARCHAR(100) NOT NULL,
[previewpath] VARCHAR(150),
[gif] VARCHAR(150),
[description] VARCHAR(300) NOT NULL,
[permissions] VARCHAR(200),
[example] VARCHAR(1000),
[type] integer,
[remark] VARCHAR(300)
);
