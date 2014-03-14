/*************************************************************
2012年 5/11　日下作成
*************************************************************/
//PIC30F C30 v3.31 & MPLAB v8.84


#ifndef	_CONFIG33F_H_
#define	_CONFIG33F_H_

_FBS(BWRP_WRPROTECT_OFF & BSS_NO_FLASH);

_FGS(GWRP_OFF & GSS_OFF);

_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);

_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_OFF & FCKSM_CSDCMD);

_FWDT(WDTPOST_PS32768 & WDTPRE_PR128 & WINDIS_OFF & FWDTEN_OFF);

_FPOR(FPWRT_PWR128 & ALTI2C_OFF);

_FICD(ICS_PGD1 & JTAGEN_OFF);


/*************************************************************
_FBS(ブートセグメントの保護領域有効/無効 & ブートコードセグメントの保護領);

	ブートセグメントの保護領域有効/無効
		BWRP_WRPROTECT_ON    ブートセグメントの保護有効
	    BWRP_WRPROTECT_OFF   ブートセグメントの保護無効
	
	ブートコードセグメントの保護領
		BSS_LARGE_FLASH_HIGH 
	    BSS_HIGH_LARGE_BOOT_CODEHigh
		BSS_MEDIUM_FLASH_HIGHHigh
		BSS_HIGH_MEDIUM_BOOT_CODEHigh
	    BSS_SMALL_FLASH_HIGH High 
	    BSS_HIGH_SMALL_BOOT_CODEHigh 
	    BSS_LARGE_FLASH_STD  
	    BSS_STRD_LARGE_BOOT_CODEStandard 
	    BSS_MEDIUM_FLASH_STD Standard 
	    BSS_STRD_MEDIUM_BOOT_CODEStandard 
	    BSS_SMALL_FLASH_STD  Standard 
	    BSS_STRD_SMALL_BOOT_CODEStandard 
	    BSS_NO_FLASH        				 ：保護領機能無し
	    BSS_NO_BOOT_CODE				     ：保護領機能無し
		
_FGS(コードプロテクトの有無 & コードプロテクトの領域);

	コードプロテクトの有無
		GWRP_ON		：コードプロテクトあり
		GWRP_OFF	：コードプロテクトなし 
		
	コードプロテクトの領域なし
		GSS_HIGH    
	    GSS_STD     
	    GCP_ON      
	    GSS_OFF     ：コードプロテクトの領域なし
	    GCP_OFF		：コードプロテクトの領域なし

_FOSCSEL(発信源とPLLの有効/無効 & FRCでスタートアップし、ユーザー選択の発振器がレディになった時の自動切り替えの有効/無効);

	発信源とPLLの有効/無効
		FNOSC_FRC            ：内部発信(FRC)
	    FNOSC_FRCPLL         ：内部発信 (FRC) PLLをオン
	    FNOSC_PRI            ：外部発信 (XT, HS, EC)
	    FNOSC_PRIPLL         ：外部発信 (XT, HS, EC) PLLをオン
	    FNOSC_SOSC           ：(SOSC)
	    FNOSC_LPRC           ：(LPRC)
	    FNOSC_FRCDIV16       ：内部発信(FRC/16)
	    FNOSC_LPRCDIVN       ：内部発信(FRC/N)
	
	発信機の自動切り換えの有効/無効
		IESO_OFF             ：ユーザー選択の発信器でスタート
		IESO_ON              ：FRCでスタートアップし、ユーザー選択の発振器がレディになった時に自動的に切り替える


_FOSC(主発振器の選択 & OSC2ピンの機能選択 & I/Oピンの再コンフィギュレーションの有効/無効 & クロック切り替え設定);

	主発振器の選択
 
		POSCMD_EC            ：主発信器オン(EC 0.8~64MHz)
		POSCMD_XT            ：主発信器オン(XT 3MHz~10Mhz)
		POSCMD_HS            ：主発信器オン(HS 10MHz~40MHz)
		POSCMD_NONE          ：主発信器オフ
 	
	OSC2ピンの機能選択
 		OSCIOFNC_ON          ：OSC2は汎用IOに設定
		OSCIOFNC_OFF         ：OSC2はクロック出力に設定
	
	I/Oピンの再コンフィギュレーションの有効/無効
		IOL1WAY_OFF          ：I/Oピンの再コンフィギュレーションの有効
	    IOL1WAY_ON           ：I/Oピンの再コンフィギュレーションの無効
		
	クロック切り替え機能の有無
 		FCKSM_CSDCMD  		 ：ともにOFF 
		FCKSM_CSECMD		 ：クロック切り替えは可。フェイルセーフ・クロックモニターはOFF 
		FCKSM_CSECME		 ：ともにON
	
_FWDT(ポストスケーラの設定 & プリスケーラの設定 & ウォッチドッグタイマの有効/無効);

	ポストスケーラの設定
		WDTPOST_PS1          1:1
		WDTPOST_PS2          1:2
	    WDTPOST_PS4          1:4
	    WDTPOST_PS8          1:8
	    WDTPOST_PS16         1:16
		WDTPOST_PS32         1:32
	    WDTPOST_PS64         1:64
	    WDTPOST_PS128        1:128
	    WDTPOST_PS256        1:256
	    WDTPOST_PS512        1:512
	    WDTPOST_PS1024       1:1,024
	    WDTPOST_PS2048       1:2,048
	    WDTPOST_PS4096       1:4,096
	    WDTPOST_PS8192       1:8,192
	    WDTPOST_PS16384      1:16,384
	    WDTPOST_PS32768      1:32,768
	
	プリスケーラの設定
		WDTPRE_PR32			1:32
	    WDTPRE_PR128       	1:128
		
	ウォッチドッグタイマの有効/無効
		FWDTEN_ON		：ウォッチドッグタイマ有効 
		FWDTEN_OFF		：ウォッチドッグタイマ無効
	
_FPOR(パワーオンリセットのパルス幅 & I2Cピンの設定);	

	パワーオンリセットのパルス幅
		FPWRT_PWR1		：パワーオンリセットを使用しない（ブラウンアウトリセットのみ） 
		FPWRT_PWR2		：2msecのパルス幅 
		FPWRT_PWR4		：4msecのパルス幅 
		FPWRT_PWR8		：8msecのパルス幅
		FPWRT_PWR16		：16msecのパルス幅 
		FPWRT_PWR32		：32msecのパルス幅 
		FPWRT_PWR64		：64msecのパルス幅
		FPWRT_PWR128	：128msecのパルス幅 

	I2Cピンの設定
		ALTI2C_ON            I2CはASDA1/ASCL1
	    ALTI2C_OFF           I2CはSDA1/SCL1

_FICD(コミュニケーションポートの選択 & JTAG Portの選択);
	コミュニケーションポートの選択
		ICS_PGD3             PGC3/EMUC3 and PGD3/EMUD3
	    ICS_PGD2             PGC2/EMUC2 and PGD2/EMUD2
	    ICS_PGD1             PGC1/EMUC1 and PGD1/EMUD1

	JTAG Portの選択
	    JTAGEN_OFF           JTAGは無効
	    JTAGEN_ON            JTAGは有効
*************************************************************/
	
#endif	/* _CONFIG33F_H_ */
