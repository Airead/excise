<?php

    include("Trans.php");

    $trans = new Trans(null);

    // 交易訊息代碼
	$trans->nodes["MSG_TYPE"] = "0100";
	// 交易處理代碼
	$trans->nodes["PCODE"] = "300000"; // 一般交易請使用 300000, 月租交易請使用 303000, 月租退租請使用 330000
	// 商家遊戲代碼
	$trans->nodes["CID"] = "C000010000068";
	// 商家訂單編號
	$trans->nodes["COID"] = "CP" . date("YmdHis");
	// 幣別 ISO Alpha Code
	$trans->nodes["CUID"] = "TWD";
	// 付款代收業者代碼
	$trans->nodes["PAID"] = "TELCHT03"; // 此範例為台灣大哥大一般型, 月租交易請使用 TELTCC02
	// 交易金額
	$trans->nodes["AMOUNT"] = "1";
	// 商家接收交易結果網址
	$trans->nodes["RETURN_URL"] = "http://localhost:20080/PHP/SampleCode_ReturnURL.php";
	//http://localhost:20080/PHP/SampleCode_Transaction.php
	// 是否指定付款代收業者
	$trans->nodes["ORDER_TYPE"] = "M"; // 請固定填 M
	// 交易備註 ( 此為選填 )
	$trans->nodes["MEMO"] = "測試交易"; // 請填寫此筆交易之備註內容
	// 樂點卡ERP商品代碼 ( 此為選填 )
	$trans->nodes["ERP_ID"] = "J990001";
	// 商家商品名稱 ( 此為選填 )
	$trans->nodes["PRODUCT_NAME"] = "商家商品 I";
	// 商家商品代碼 ( 此為選填 )
	$trans->nodes["PRODUCT_ID"] = "";
	// 玩家帳號 ( 此為選填 )
	$trans->nodes["USER_ACCTID"] = "";
	// 以商家密碼、商家密鑰 I , II ( 已於 Common.php 內設定 ) 取得 ERQC
	$erqc = $trans->GetERQC( $p, $k, $v );
	// 商家交易驗證壓碼
	$trans->nodes["ERQC"] = $erqc;

    $xml = $trans->xmlDoc;

    echo "data: \n";
    echo $trans->GenerateXmlDoc();
?>