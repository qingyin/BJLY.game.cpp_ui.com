#import "iOSPlatform.h"

#include "IosHelper.h"
#include "view/Layer/Menu/GameMenu.h"
#include "model/GamerData.h"
//#include "model/PlayerInfoModel.h"
#include "platform/MissionWeiXin.h"

@implementation WXApiManager

#pragma mark - LifeCycle
+(instancetype)sharedManager {
    static dispatch_once_t onceToken;
    static WXApiManager *instance;
    dispatch_once(&onceToken, ^{
        instance = [[WXApiManager alloc] init];
    });
    return instance;
}

- (void)dealloc {
    self.delegate = nil;
    [super dealloc];
}

#pragma mark - WXApiDelegate
- (void)onResp:(BaseResp *)resp {
    
    NSLog(@"onResp-------");
    if (WXSuccess == resp.errCode)
    {
        if ([resp isKindOfClass:[SendAuthResp class]])
        {
            SendAuthResp *temp = (SendAuthResp *)resp;
            NSLog(@"%@",temp.code);
            
            NSString *AppId=@"wx9ac9ddb90cdcadb7";
            NSString *AppSerect=@"257306b69877fa65bf2259e4d977bff3";
            NSString *url =[NSString stringWithFormat:@"https://api.weixin.qq.com/sns/oauth2/access_token?appid=%@&secret=%@&code=%@&grant_type=authorization_code",AppId,AppSerect,temp.code];
            
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                NSURL *zoneUrl = [NSURL URLWithString:url];
                NSString *zoneStr = [NSString stringWithContentsOfURL:zoneUrl encoding:NSUTF8StringEncoding error:nil];
                NSData *data = [zoneStr dataUsingEncoding:NSUTF8StringEncoding];
                dispatch_async(dispatch_get_main_queue(), ^{
                    if (data){
                        NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
                        NSString *openID = dic[@"openid"];
                        NSString *unionid = dic[@"unionid"];
                        NSString *accesstoken = dic[@"access_token"];
                        NSLog(@"%@",dic);
                        NSLog(@"%@",openID);
                        NSLog(@"%@",unionid);
                        std::string acc=[accesstoken UTF8String];
                        std::string open=[openID UTF8String];
                        cocos2d::UserDefault::getInstance()->setStringForKey("accesstoken",acc.c_str());
                        cocos2d::UserDefault::getInstance()->setStringForKey("openid",open.c_str());
                        [self getuerinfo:accesstoken :openID];
                    }
                });
            });
        }
    }
    
   }
-(void)getuerinfo:(NSString *)token :(NSString *)openid
{
    NSString *url =[NSString stringWithFormat:@"https://api.weixin.qq.com/sns/userinfo?access_token=%@&openid=%@",token,openid];
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSURL *zoneUrl = [NSURL URLWithString:url];
        NSString *zoneStr = [NSString stringWithContentsOfURL:zoneUrl encoding:NSUTF8StringEncoding error:nil];
        NSData *data = [zoneStr dataUsingEncoding:NSUTF8StringEncoding];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (data)
            {
                NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
                int errorcode=[dic[@"errcode"] integerValue];
                if(errorcode!=0)
                {
                    cocos2d::UserDefault::getInstance()->setStringForKey("accesstoken","");
                    cocos2d::UserDefault::getInstance()->setStringForKey("openid","");
                    WeiChatLogin::getInstance()->sendAuthReq();
                    return;
                }
                NSLog(@"%@",dic);
                NSString *name=dic[@"nickname"];
                std::string name1=[name UTF8String];
                NSString *url=dic[@"headimgurl"];
                std::string url1=[url UTF8String];
                std::string open=[openid UTF8String];
                int sex=[dic[@"sex"] integerValue];
                
                
                GamerData::getInstance()->setNick(name1);
                GamerData::getInstance()->setHeadUrl(url1);
                GamerData::getInstance()->setOpenid(open);
                GamerData::getInstance()->setSex(sex);
                
                
                UserDefault::getInstance()->setBoolForKey("isAutoLogon",true);
                
                
                MissionWeiXin::getinstance()->req_login();
            }
        });
    });
}


-(float)getPower
{
    return 1.2;
}
@end
