<?php
//don't allow otherscripts to grab and execute our file
defined('_JEXEC') or die('Direct Access to this location is not allowed.');

//This is the parameter we get from our xml file above
$height = $params->get('height');
$width = $params->get('width');
$link = $params->get('link');
$suffix = $params->get('suffix');
$is_background = $params->get('is_background');

//Include the syndicate functions only once
require_once dirname(__FILE__).'/helper.php';

$products = getProductsView($suffix);
//Returns the path of the layout file
require JModuleHelper::getLayoutPath('mod_product_view', $params->get('layout', 'default'));
?>
