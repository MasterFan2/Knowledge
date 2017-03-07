//SDK插入数据
insert into sdk(name,sdkVersion,remark) values("Lolli",23,"Haha");

//widget
insert into widget(name,className,previewpath,gif,description,permissions,example,type,remark)
values("下拉刷新","RefreshLayout","./preview/refresh.jpg","./gif/refresh.gif", "不错的下拉刷新控件", "android.permission.INTERNET","这是示例代码",2,"注意使用");

//projectDir
insert into projectDir(dirName,remark) values("res/layout","这是布局文件目录");

//projectFile
insert into projectFile(widgetId,dirId, fileDir, fileName,description) values(1, 1, "res/layout","refresh.xml", "这是下拉刷新的布局文件");
