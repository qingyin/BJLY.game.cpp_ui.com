<GameFile>
  <PropertyGroup Name="GameMenu" Type="Layer" ID="dc38688c-b51f-4675-a29e-fa73cbce65b4" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="50" Speed="1.0000">
        <Timeline ActionTag="-162589943" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="-1">
              <Points>
                <PointF />
                <PointF />
                <PointF X="1.0000" Y="1.0000" />
                <PointF X="1.0000" Y="1.0000" />
              </Points>
            </EasingData>
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="0.5000" Y="0.5000">
            <EasingData Type="-1">
              <Points>
                <PointF />
                <PointF />
                <PointF X="1.0000" Y="1.0000" />
                <PointF X="1.0000" Y="1.0000" />
              </Points>
            </EasingData>
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="anim_gift" StartIndex="0" EndIndex="50">
          <RenderColor A="255" R="238" G="232" B="170" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Layer" Tag="13" ctype="GameLayerObjectData">
        <Size X="1280.0000" Y="720.0000" />
        <Children>
          <AbstractNodeData Name="bg_index_1" ActionTag="-692434985" Tag="1017" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" ctype="SpriteObjectData">
            <Size X="1280.0000" Y="720.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="640.0000" Y="360.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="loading/lobbyPic/bg_index.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="slogan_1" ActionTag="-163276186" Tag="91" IconVisible="False" LeftMargin="532.0001" RightMargin="531.9999" TopMargin="9.2613" BottomMargin="567.7387" ctype="SpriteObjectData">
            <Size X="216.0000" Y="143.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="640.0001" Y="639.2387" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.8878" />
            <PreSize X="0.1688" Y="0.1986" />
            <FileData Type="Normal" Path="loading/lobbyPic/slogan.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="goldBarBg" ActionTag="-1398898539" Tag="1358" IconVisible="False" LeftMargin="131.6033" RightMargin="828.3967" TopMargin="18.0941" BottomMargin="586.9059" ctype="SpriteObjectData">
            <Size X="320.0000" Y="115.0000" />
            <Children>
              <AbstractNodeData Name="icon_fangka_7" ActionTag="1164841833" Tag="1355" IconVisible="False" LeftMargin="30.9591" RightMargin="239.0409" TopMargin="73.0616" BottomMargin="2.9384" ctype="SpriteObjectData">
                <Size X="50.0000" Y="39.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="55.9591" Y="22.4384" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1749" Y="0.1951" />
                <PreSize X="0.1563" Y="0.3391" />
                <FileData Type="Normal" Path="loading/lobbyPic/icon_fangka.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="goldNum" ActionTag="907123444" Tag="1357" IconVisible="False" LeftMargin="83.4027" RightMargin="193.5973" TopMargin="74.0600" BottomMargin="6.9400" FontSize="28" LabelText="123" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="43.0000" Y="34.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="83.4027" Y="23.9400" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="199" G="168" B="81" />
                <PrePosition X="0.2606" Y="0.2082" />
                <PreSize X="0.1344" Y="0.2957" />
                <FontResource Type="Normal" Path="fonts/FangZhengZhunYuan.TTF" Plist="" />
                <OutlineColor A="255" R="255" G="255" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btnAddGold" ActionTag="1091547965" VisibleForFrame="False" Tag="23" IconVisible="False" LeftMargin="136.0000" RightMargin="136.0000" TopMargin="67.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="48.0000" Y="48.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="160.0000" Y="24.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2087" />
                <PreSize X="0.1500" Y="0.4174" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="img_click" ActionTag="9157909" Tag="320" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="17.0080" RightMargin="82.9920" TopMargin="36.4980" BottomMargin="-1.4980" TouchEnable="True" LeftEage="9" RightEage="9" TopEage="9" BottomEage="9" Scale9OriginX="9" Scale9OriginY="9" Scale9Width="12" Scale9Height="12" ctype="ImageViewObjectData">
                <Size X="220.0000" Y="80.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="127.0080" Y="38.5020" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3969" Y="0.3348" />
                <PreSize X="0.6875" Y="0.6957" />
                <FileData Type="Normal" Path="loading/lobbyPic/img_transparent.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn_addCard" ActionTag="-2089014592" Tag="1356" IconVisible="False" LeftMargin="177.1884" RightMargin="105.8116" TopMargin="71.0616" BottomMargin="5.9384" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="8" Scale9Height="17" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="37.0000" Y="38.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="195.6884" Y="24.9384" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.6115" Y="0.2169" />
                <PreSize X="0.1156" Y="0.3304" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="loading/lobbyPic/bg_add_down.png" Plist="" />
                <NormalFileData Type="Normal" Path="loading/lobbyPic/bg_add.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="291.6033" Y="644.4059" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2278" Y="0.8950" />
            <PreSize X="0.2500" Y="0.1597" />
            <FileData Type="Normal" Path="loading/lobbyPic/bg_nameID.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="nickName" ActionTag="-472292975" Tag="19" IconVisible="False" LeftMargin="162.5624" RightMargin="1065.4376" TopMargin="24.6055" BottomMargin="666.3945" FontSize="24" LabelText="朱锋" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="52.0000" Y="29.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="162.5624" Y="680.8945" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="247" G="212" B="106" />
            <PrePosition X="0.1270" Y="0.9457" />
            <PreSize X="0.0406" Y="0.0403" />
            <FontResource Type="Normal" Path="fonts/FangZhengZhunYuan.TTF" Plist="" />
            <OutlineColor A="255" R="255" G="165" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="userId" ActionTag="-2137273215" Tag="20" IconVisible="False" LeftMargin="162.5624" RightMargin="977.4376" TopMargin="57.3976" BottomMargin="633.6024" FontSize="24" LabelText="ID:123456789" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="140.0000" Y="29.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="162.5624" Y="648.1024" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="247" G="212" B="106" />
            <PrePosition X="0.1270" Y="0.9001" />
            <PreSize X="0.1094" Y="0.0403" />
            <FontResource Type="Normal" Path="fonts/FangZhengZhunYuan.TTF" Plist="" />
            <OutlineColor A="255" R="255" G="165" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="sprite_headImg" ActionTag="-136127505" Tag="371" IconVisible="False" LeftMargin="28.7000" RightMargin="1146.3000" TopMargin="19.6000" BottomMargin="595.4000" ctype="SpriteObjectData">
            <Size X="105.0000" Y="105.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="81.2000" Y="647.9000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0634" Y="0.8999" />
            <PreSize X="0.0820" Y="0.1458" />
            <FileData Type="Normal" Path="loading/lobbyPic/default_head.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_head" ActionTag="1044867834" CallBackType="Touch" Tag="164" IconVisible="False" LeftMargin="20.0479" RightMargin="1133.9521" TopMargin="11.5692" BottomMargin="584.4308" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="96" Scale9Height="102" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="126.0000" Y="124.0000" />
            <Children>
              <AbstractNodeData Name="iconUser" ActionTag="-1744351602" VisibleForFrame="False" Tag="18" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="10.5000" RightMargin="10.5000" TopMargin="9.5000" BottomMargin="9.5000" ctype="SpriteObjectData">
                <Size X="105.0000" Y="105.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="63.0000" Y="62.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.8333" Y="0.8468" />
                <FileData Type="Normal" Path="loading/lobbyPic/default_head.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="83.0479" Y="646.4308" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0649" Y="0.8978" />
            <PreSize X="0.0984" Y="0.1722" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="loading/lobbyPic/frame_head.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/frame_head.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/frame_head.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnShare" ActionTag="1884462246" VisibleForFrame="False" Tag="25" IconVisible="False" LeftMargin="321.7396" RightMargin="869.2604" TopMargin="645.5559" BottomMargin="-1.5559" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="59" Scale9Height="54" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="89.0000" Y="76.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="366.2396" Y="36.4441" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2861" Y="0.0506" />
            <PreSize X="0.0695" Y="0.1056" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="loading/gamemenu/qd2x_0002_tg-1.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/gamemenu/qd2x_0002_tg-1.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/gamemenu/qd2x_0007_tg.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnNotice" ActionTag="987272630" VisibleForFrame="False" Tag="26" IconVisible="False" LeftMargin="236.6657" RightMargin="969.3343" TopMargin="645.6641" BottomMargin="7.3359" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="44" Scale9Height="45" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="74.0000" Y="67.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="273.6657" Y="40.8359" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2138" Y="0.0567" />
            <PreSize X="0.0578" Y="0.0931" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="loading/gamemenu/qd2x_0003_xx-1.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/gamemenu/qd2x_0003_xx-1.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/gamemenu/qd2x_0008_xx.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnGet" ActionTag="-1032611575" VisibleForFrame="False" Tag="30" IconVisible="False" LeftMargin="1168.5000" RightMargin="18.5000" TopMargin="126.0000" BottomMargin="486.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="93.0000" Y="108.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1215.0000" Y="540.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9492" Y="0.7500" />
            <PreSize X="0.0727" Y="0.1500" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnNewPlayer" ActionTag="14529357" VisibleForFrame="False" Tag="31" IconVisible="False" LeftMargin="1157.2188" RightMargin="30.7813" TopMargin="122.5534" BottomMargin="508.4466" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="62" Scale9Height="67" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="92.0000" Y="89.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1203.2188" Y="552.9466" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9400" Y="0.7680" />
            <PreSize X="0.0719" Y="0.1236" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Normal" Path="loading/gamemenu/qd2x_0002_xs.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/gamemenu/qd2x_0002_xs.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/gamemenu/qd2x_0001_xs.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="qd2x_0021_bd_1" ActionTag="815354285" VisibleForFrame="False" Tag="325" IconVisible="False" LeftMargin="80.3788" RightMargin="813.6212" TopMargin="215.5759" BottomMargin="50.4241" ctype="SpriteObjectData">
            <Size X="386.0000" Y="454.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="273.3788" Y="277.4241" />
            <Scale ScaleX="1.0000" ScaleY="0.9750" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2136" Y="0.3853" />
            <PreSize X="0.3016" Y="0.6306" />
            <FileData Type="Normal" Path="loading/gamemenu/qd2x_0021_bd.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="iconTip" ActionTag="1161084123" VisibleForFrame="False" Tag="32" IconVisible="False" LeftMargin="105.8127" RightMargin="856.1873" TopMargin="234.8123" BottomMargin="90.1877" Scale9Width="318" Scale9Height="395" ctype="ImageViewObjectData">
            <Size X="318.0000" Y="395.0000" />
            <Children>
              <AbstractNodeData Name="Text_1" ActionTag="784887442" Tag="281" IconVisible="False" LeftMargin="28.3205" RightMargin="37.6795" TopMargin="40.5997" BottomMargin="318.4003" FontSize="36" LabelText="本游戏仅为娱乐" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="252.0000" Y="36.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="154.3205" Y="336.4003" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="243" G="232" B="234" />
                <PrePosition X="0.4853" Y="0.8516" />
                <PreSize X="0.7925" Y="0.0911" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_2" ActionTag="-102868763" Tag="282" IconVisible="False" LeftMargin="82.3205" RightMargin="91.6795" TopMargin="91.7059" BottomMargin="267.2941" FontSize="36" LabelText="禁止赌博" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="144.0000" Y="36.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="154.3205" Y="285.2941" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4853" Y="0.7223" />
                <PreSize X="0.4528" Y="0.0911" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_3" ActionTag="-1177511541" Tag="283" IconVisible="False" LeftMargin="28.3205" RightMargin="37.6795" TopMargin="145.0839" BottomMargin="213.9161" FontSize="36" LabelText="首次加客服微信" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="252.0000" Y="36.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="154.3205" Y="231.9161" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4853" Y="0.5871" />
                <PreSize X="0.7925" Y="0.0911" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_4" ActionTag="1481339014" Tag="284" IconVisible="False" LeftMargin="73.3205" RightMargin="82.6795" TopMargin="196.3823" BottomMargin="162.6177" FontSize="36" LabelText="123456789" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="162.0000" Y="36.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="154.3205" Y="180.6177" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4853" Y="0.4573" />
                <PreSize X="0.5094" Y="0.0911" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_5" ActionTag="-1897449973" Tag="285" IconVisible="False" LeftMargin="30.3196" RightMargin="27.6804" TopMargin="245.7817" BottomMargin="109.2183" FontSize="40" LabelText="免费领取8颗钻" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="260.0000" Y="40.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="160.3196" Y="129.2183" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5041" Y="0.3271" />
                <PreSize X="0.8176" Y="0.1013" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="264.8127" Y="287.6877" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2069" Y="0.3996" />
            <PreSize X="0.2484" Y="0.5486" />
            <FileData Type="Normal" Path="loading/gamemenu/qd2x_0017_hong.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="panelNotice" ActionTag="-372957284" Tag="35" IconVisible="False" LeftMargin="116.9623" RightMargin="63.0377" TopMargin="144.4514" BottomMargin="534.5486" TouchEnable="True" ClipAble="True" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1100.0000" Y="41.0000" />
            <Children>
              <AbstractNodeData Name="noticeBg" ActionTag="1750655601" Tag="33" IconVisible="False" LeftMargin="-18.2511" RightMargin="147.2511" TopMargin="1.1158" BottomMargin="0.8842" ctype="SpriteObjectData">
                <Size X="971.0000" Y="39.0000" />
                <AnchorPoint />
                <Position X="-18.2511" Y="0.8842" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="-0.0166" Y="0.0216" />
                <PreSize X="0.8827" Y="0.9512" />
                <FileData Type="Normal" Path="loading/lobbyPic/bg_tongzhi.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_notice" ActionTag="1040806148" Tag="286" IconVisible="False" LeftMargin="1100.6522" RightMargin="-1029.6523" TopMargin="3.0000" BottomMargin="2.0000" FontSize="32" LabelText="欢迎进入百乐麻将,新手免费领取8张房卡 欢迎关注官方微信：123445556。" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="1029.0000" Y="36.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="1100.6522" Y="20.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="244" G="241" B="144" />
                <PrePosition X="1.0006" Y="0.4878" />
                <PreSize X="0.9355" Y="0.8780" />
                <FontResource Type="Normal" Path="fonts/FangZhengZhunYuan.TTF" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="116.9623" Y="534.5486" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0914" Y="0.7424" />
            <PreSize X="0.8594" Y="0.0569" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sprite_9" ActionTag="-237301102" Tag="2065" IconVisible="False" LeftMargin="79.5264" RightMargin="1148.4736" TopMargin="141.0377" BottomMargin="526.9623" ctype="SpriteObjectData">
            <Size X="52.0000" Y="52.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="105.5264" Y="552.9623" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0824" Y="0.7680" />
            <PreSize X="0.0406" Y="0.0722" />
            <FileData Type="Normal" Path="loading/lobbyPic/icon_laba.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnBackRoom" ActionTag="-1757844882" VisibleForFrame="False" Tag="38" IconVisible="False" LeftMargin="877.1100" RightMargin="84.8900" TopMargin="233.1100" BottomMargin="91.8900" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="288" Scale9Height="373" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="318.0000" Y="395.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1036.1100" Y="289.3900" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8095" Y="0.4019" />
            <PreSize X="0.2484" Y="0.5486" />
            <TextColor A="255" R="65" G="65" B="70" />
            <NormalFileData Type="Normal" Path="loading/gamemenu/dd1.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="gg_4" ActionTag="88256498" VisibleForFrame="False" Tag="328" IconVisible="False" LeftMargin="103.8893" RightMargin="858.1107" TopMargin="539.0335" BottomMargin="85.9665" ctype="SpriteObjectData">
            <Size X="318.0000" Y="95.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="262.8893" Y="133.4665" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2054" Y="0.1854" />
            <PreSize X="0.2484" Y="0.1319" />
            <FileData Type="Normal" Path="loading/gamemenu/gg.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnSet" ActionTag="1516855145" Tag="1018" IconVisible="False" LeftMargin="1160.5424" RightMargin="19.4576" TopMargin="12.5692" BottomMargin="605.4308" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="80" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="100.0000" Y="102.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1210.5424" Y="656.4308" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9457" Y="0.9117" />
            <PreSize X="0.0781" Y="0.1417" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/icon_set_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/icon_set.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_msg" ActionTag="180111037" Tag="1019" IconVisible="False" LeftMargin="1033.1790" RightMargin="146.8210" TopMargin="12.5692" BottomMargin="605.4308" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="80" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="100.0000" Y="102.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1083.1790" Y="656.4308" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8462" Y="0.9117" />
            <PreSize X="0.0781" Y="0.1417" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/icon_message_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/icon_message.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnShareCircle" ActionTag="-1245493952" Tag="1020" IconVisible="False" LeftMargin="905.8180" RightMargin="274.1820" TopMargin="12.5692" BottomMargin="605.4308" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="70" Scale9Height="80" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="100.0000" Y="102.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="955.8180" Y="656.4308" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7467" Y="0.9117" />
            <PreSize X="0.0781" Y="0.1417" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/icon_share_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/icon_share.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnJoinRoom" ActionTag="1020963682" Tag="1021" IconVisible="False" LeftMargin="867.5422" RightMargin="60.4578" TopMargin="237.6761" BottomMargin="178.3239" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="322" Scale9Height="282" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="352.0000" Y="304.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1043.5422" Y="330.3239" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8153" Y="0.4588" />
            <PreSize X="0.2750" Y="0.4222" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/button_join_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/button_join.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnCreateRoom" ActionTag="911174125" Tag="1022" IconVisible="False" LeftMargin="416.8724" RightMargin="511.1276" TopMargin="237.6761" BottomMargin="178.3239" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="322" Scale9Height="282" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="352.0000" Y="304.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="592.8724" Y="330.3239" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4632" Y="0.4588" />
            <PreSize X="0.2750" Y="0.4222" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/button_found_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/button_found.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnHelp" ActionTag="-1985880740" Tag="1031" IconVisible="False" HorizontalEdge="RightEdge" LeftMargin="385.1040" RightMargin="787.8960" TopMargin="601.9934" BottomMargin="11.0066" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="77" Scale9Height="85" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="107.0000" Y="107.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="438.6040" Y="64.5066" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.3427" Y="0.0896" />
            <PreSize X="0.0836" Y="0.1486" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/icon_wanfa_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/icon_wanfa.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btnAchievement" ActionTag="535962118" Tag="1302" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="TopEdge" LeftMargin="774.4260" RightMargin="398.5740" TopMargin="601.9934" BottomMargin="11.0066" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="77" Scale9Height="85" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="107.0000" Y="107.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="827.9260" Y="64.5066" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.6468" Y="0.0896" />
            <PreSize X="0.0836" Y="0.1486" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/icon_zhanji_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/icon_zhanji.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_feedback" ActionTag="-1497193479" Tag="1348" IconVisible="False" HorizontalEdge="BothEdge" VerticalEdge="BothEdge" LeftMargin="969.0920" RightMargin="203.9080" TopMargin="601.9880" BottomMargin="11.0120" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="77" Scale9Height="85" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="107.0000" Y="107.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1022.5920" Y="64.5120" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7989" Y="0.0896" />
            <PreSize X="0.0836" Y="0.1486" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/icon_fankui_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/icon_fankui.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_activity" ActionTag="-408468709" Tag="1349" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="579.7650" RightMargin="593.2350" TopMargin="601.9934" BottomMargin="11.0066" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="77" Scale9Height="85" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="107.0000" Y="107.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="633.2650" Y="64.5066" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="229" G="229" B="229" />
            <PrePosition X="0.4947" Y="0.0896" />
            <PreSize X="0.0836" Y="0.1486" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/icon_activity_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/icon_activity.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="btn_binding" ActionTag="-989125047" Tag="1350" IconVisible="False" LeftMargin="190.4432" RightMargin="982.5568" TopMargin="601.9934" BottomMargin="11.0066" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="77" Scale9Height="85" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="107.0000" Y="107.0000" />
            <Children>
              <AbstractNodeData Name="tip_gift" ActionTag="-162589943" Tag="1351" IconVisible="False" LeftMargin="-29.0258" RightMargin="63.0258" TopMargin="-33.9137" BottomMargin="87.9137" ctype="SpriteObjectData">
                <Size X="73.0000" Y="53.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="7.4742" Y="114.4137" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0699" Y="1.0693" />
                <PreSize X="0.6822" Y="0.4953" />
                <FileData Type="Normal" Path="loading/lobbyPic/tip_youli.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="243.9432" Y="64.5066" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1906" Y="0.0896" />
            <PreSize X="0.0836" Y="0.1486" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="loading/lobbyPic/icon_bangding_down.png" Plist="" />
            <NormalFileData Type="Normal" Path="loading/lobbyPic/icon_bangding.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="bg_advertisment_3" ActionTag="-1016242195" Tag="1352" IconVisible="False" LeftMargin="39.6791" RightMargin="935.3209" TopMargin="220.6765" BottomMargin="154.3235" ctype="SpriteObjectData">
            <Size X="305.0000" Y="345.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="192.1791" Y="326.8235" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1501" Y="0.4539" />
            <PreSize X="0.2383" Y="0.4792" />
            <FileData Type="Normal" Path="loading/lobbyPic/bg_advertisment.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>