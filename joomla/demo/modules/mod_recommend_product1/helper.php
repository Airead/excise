<?php
//No access
defined('_JEXEC') or die;

$com_path = JPATH_SITE.'/components/com_content/';
require_once $com_path.'router.php';
require_once $com_path.'helpers/route.php';

JModelLegacy::addIncludePath($com_path . '/models', 'ContentModel');

//Add database instance
$db = JFactory::getDBO();

function getProducts($suffix) {
  $db = JFactory::getDBO();
  $query = "SELECT id FROM #__categories where title='recommend product".$suffix."'";
  //Run it
  $db->setQuery($query);

  //Load it as an object into the variable "$rows"
  $row = $db->loadObject();
  $catid = $row->id;

  // get articles
  $query2 = "SELECT * FROM #__content where catid='".$catid."'";
  //echo $query2;
  $db->setQuery($query2);
  $rows = $db->loadObjectList();

  $count = 0;
  foreach ($rows as $row) {
    $products[$count]->title = $row->title;
    $products[$count]->introtext = $row->introtext;
    $images = json_decode($row->images);
    $products[$count]->image_intro = $images->image_intro;
    $urls = json_decode($row->urls);
    $products[$count]->urla = $urls->urla;
    $count = $count + 1;
  }
  return $products;
}

?>