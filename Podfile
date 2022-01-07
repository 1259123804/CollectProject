source 'https://github.com/CocoaPods/Specs.git'
platform :ios, '9.0'
inhibit_all_warnings!
use_modular_headers!

# 解决TXIMSDK_TUIKit_iOS、TXIMSDK_TUIKit_live_iOS 不支持 New Build System
install! 'cocoapods', :disable_input_output_paths => true

target 'SmoothNavDemo' do
  # 常用第三方依赖
  pod 'MBProgressHUD'
  pod 'IQKeyboardManager'
  pod 'JXCategoryView'
  pod 'IAPHelper'
  pod 'SVGAPlayer'
  pod "Masonry"
  pod 'SDCycleScrollView'
  pod 'KVOController'
  pod 'BRPickerView'
  pod 'TZImagePickerController'
  #pod 'ReactiveObjC'
	# pod 'iCarousel'
  pod 'GKCycleScrollView'
  pod 'FLAnimatedImage'
  pod "SDWebImage"
  pod 'KNPhotoBrowser'
  # shareSDK分享
  pod 'mob_smssdk'
  pod 'mob_sharesdk'
  pod 'mob_sharesdk/ShareSDKUI'
  #pod 'mob_sharesdk/ShareSDKPlatforms/QQ'
  #pod 'mob_sharesdk/ShareSDKPlatforms/SinaWeibo'
  #pod 'mob_sharesdk/ShareSDKPlatforms/WeChatFull'
  pod 'mob_sharesdk/ShareSDKPlatforms/Facebook'
  
  #支付宝
  #pod 'AlipaySDK-iOS’
  
  # NSMKit依赖
  pod 'AFNetworking'
  pod 'DZNEmptyDataSet'
  pod 'MJRefresh'
  pod 'YYKit'
  pod 'MyLayout'
  pod 'LFMediaEditingController'
  
  # 极光推送
  pod 'JPush', '~> 3.6.2'
  
  # 腾讯IM带
  pod 'TXIMSDK_TUIKit_iOS', '~> 5.1.56'
  # 腾讯直播带UI
  #pod 'TXIMSDK_TUIKit_live_iOS', '~> 5.1.56'
  
  # 美颜-相芯
 # pod 'Nama','~> 7.3.0'
  pod 'SVProgressHUD'
  pod 'CYLTabBarController'
  #pod 'MQTTKit', :git => 'https://github.com/mobile-web-messaging/MQTTKit.git'
  #pod 'MQTTClient/Min'
  #pod 'MQTTClient/Manager'
end

post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      config.build_settings['IPHONEOS_DEPLOYMENT_TARGET'] = '9.0'
    end
  end
end



