
1.windows用的是VS2012集成开发环境
2.拷贝引擎cocos2d（win32用v3.9版本的，mac下用v3.10版本的）到当前目录
3.把Other文件夹下的protobuf-2.5.0.rar解压到cocos2d\external文件夹下
4.把Other文件夹下的bugly.zip解压到cocos2d\external文件夹下
5.拷贝资源到Resources\res（可以设置cocosStudio导出的路径为此路径，就不需要手动来拷贝了）
6.android编译命令
cocos compile -p android -m release
//第一次需要配置签名文件，之后就可以直接打出包来了，不用打开eclipse或androidStudio来导出apk文件了