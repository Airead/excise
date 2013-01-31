<?php
/**
* @package		Joomla.Site
* @copyright	Copyright (C) 2012 Airead Fan, Inc. All rights reserved.
* @license		GNU General Public License version 2 or later; see LICENSE.txt
*/

defined('_JEXEC') or die;

/* The following line loads the MooTools JavaScript Library */
JHtml::_('behavior.framework', true);

// check modules
$showNews = ($this->countModules('wwl-news'));
$showMenu = ($this->countModules('wwl-menu'));
$showCenterer = ($this->countModules('wwl-banner') or $this->countModules('wwl-news') or $this->countModules('wwl-menu'));
$showContents = ($this->countModules('wwl-whoweare') or $this->countModules('wwl-recommend1') or $this->countModules('wwl-recommend2'));

$doc = JFactory::getDocument();
$doc->addStyleSheet($this->baseurl.'/templates/'.$this->template.'/css/template.css', $type = 'text/css', $media = 'screen,projection');

?>
<?php echo '<?'; ?>xml version="1.0" encoding="<?php echo $this->_charset ?>"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $this->language; ?>" lang="<?php echo $this->language; ?>" dir="<?php echo $this->direction; ?>" >
  <head>
    <!-- The following JDOC Head tag loads all the header and meta information from your site config and content. -->
    <jdoc:include type="head" />
  </head> 
  <body>
    <div id="header">
      <div id="heads">
        <div id="logo"></div>
        <div id="language"><a href="/china/" target="_blank">Chinese</a></div>
        <h1>Briquette Machine</h1>
        <br class="clear">
      </div>
    </div>
    <div id="navs">
      <div id="nav">
        <jdoc:include type="modules" name="wwl-nav" />
        <div id="search">
          <jdoc:include type="modules" name="wwl-search" />
        </div>
      </div>
    </div>
    <?php if ($showCenterer): ?>
    <div id="centerer">
      <?php if ($showMenu): ?>
      <div id="menu">
        <jdoc:include type="modules" name="wwl-menu" />
      </div>
      <?php endif; ?>
      <?php if ($showNews): ?>
      <div id="centers">
        <jdoc:include type="modules" name="wwl-banner" />
        <div id="index_news">
          <div class="recent"><a href="news_1.html">Recent News &amp; Events</a></div>
          <jdoc:include type="modules" name="wwl-news" />
        </div>
        <?php endif; ?>
      </div>
    </div>
    <?php endif; ?>
    <div id="container">
      <jdoc:include type="component" />
      <?php if ($showContents): ?>
      <div id="contents">
        <jdoc:include type="modules" name="wwl-whoweare" />
        <div class="rproduct_title"><img src="templates/wwl/images/Recommend_Products.jpg" width="229" height="36" alt="Recommend_Products" border="0"></div>
        <jdoc:include type="modules" name="wwl-recommend1" />
        <jdoc:include type="modules" name="wwl-recommend2" />
      </div>
      <?php endif; ?>
      <div id="list">
        <a href="http://agitc.cn/Get-Free-Home-Oil-Extractor-from-Machinery-Manufacturer-on-Christmas.html"><img src="templates/wwl/images/christmas.gif"></a><br><br>

	<h2><a href="briquetting-presses.html">Briquette Press</a></h2>
        <ul>
          <li><a href="Charcoal.htm">Biomass Briquetting Machine</a></li>
          <li><a href="Charcoal-Powder-of-Briquetting-Plant.htm">Charcoal Power Briquetting Plant</a></li>
          <li><a href="Metal-Briquette-Press.html">Metal Briquette Press</a></li>
          <li><a href="Coal-Ball-Briquetting-Plant.html">Coal Ball Briquetting Plant</a></li>
          <li><a href="Straw-Fuel-Briquette-Press.html">Fuel Briquette Press</a></li>
          <li><a href="Shisha-Charcoal-Machine.html">Shisha Charcoal Briquette Machine</a></li>
        </ul>
        <h2><a href="pellet-mill.htm">Pellet Mill</a></h2>
        <ul>
          <li><a href="pellet-press.htm">Pellet Press</a></li>
          <li><a href="Wood-Pellet-Plant.htm">Wood Pellet Plant</a></li>
          <li><a href="wood-pellet-mill-cooler.html">Counter-flow Cooler</a></li>
          <li><a href="wood-pellet-mill-stoves.html">Wood Pellet Stove</a></li>
          <li><a href="wood-pellet-mill-pellets.html">Wood Pellets</a></li>
          <li><a href="Biomass-Gasification-Power-Plant.html">Biomass Gasification Power Plant</a></li>
          <li><a href="Mobile-Pellet-Plant.html">Mobile Pellet Plant</a></li>
        </ul>
        <h2><a href="oil-press.html">Oil Press</a></h2>
        <ul>
          <li><a href="Rapeseed-Oil-Press.html">Rapeseed Oil Press</a></li>
          <li><a href="screw-oil-expeller.html">Small Oil Press</a></li>
          <li><a href="oil-expellers.html">Large Scale Oil Press</a></li>
          <li><a href="Oil-Press-Machine.htm">Integrated Oil Press</a></li>
          <li><a href="vegetable-oil-filter-press.html">Oil Filter Press</a></li>
          <li><a href="Sunflower-Seeds-Oil-Press.html">Sunflower Seeds Oil Press</a></li>
          <li><a href="Jatropha-Oil-Press.html">Jatropha Oil Press</a></li>
          <li><a href="Soybean-Oil-Press.html">Soybean Oil Press</a></li>
          <li><a href="Sesame-Oil-Press.html">Sesame Oil Press</a></li>
          <li><a href="Hand-Oil-Press.html">Hand Oil Press</a></li>
        </ul>
        <h2><a href="flour-mill.html">Flour Mill</a></h2>
        <ul>
          <li><a href="Small-Wheat-Flour-Mill.html">Small Wheat Flour Mill</a></li>
          <li><a href="Large-Flour-Mill.html">Large Flour Mill</a></li>
          <li><a href="Flour-Milling-Machine.html">Cassava Flour Milling</a></li>
          <li><a href="maize-miller.html">Maize Miller</a></li>
        </ul>
        <h2><a href="roll-forming-machine.html">Roll Forming Machine</a></h2>
        <ul>
          <li><a href="Roof-wall-panel-roll-form-machine.html">Roof &amp; wall panel roll form machine</a></li>
          <li><a href="Glazed-tile-roll-forming-lines.html">Glazed tile roll forming lines</a></li>
          <li><a href="C-Z-purlin-cold-roll-forming-machine.html">C/Z purlin cold roll forming machine</a></li>
          <li><a href="Steel-structure-floor-roll-forming-lines.html">Steel structure floor roll forming lines</a></li>
          <li><a href="Cable-tray-roll-forming-machinery.html">Cable tray roll forming machinery</a></li>
          <li><a href="Sandwich-panel-rollforming-machine.html">Sandwich panel rollforming machine</a></li>
        </ul>
        <h2><a href="feed-machinery.html">Feed Machinery</a></h2>
        <ul>
          <li><a href="NPK-Plant.html">NPK Plant</a></li>
          <li><a href="Compound-Fertilizer-Plant.html">Compound Fertilizer Plant</a></li>
          <li><a href="Organic-Fertilizer-Plant.html">Organic Fertilizer Plant</a></li>
          <li><a href="Fertilizer-Granulator.html">Fertilizer Granulator</a></li>
          <li><a href="cattle-pellet-plant.html">Cattle Pellet Plant</a></li>
          <li><a href="poultry-pellet-plant.html">Poultry Pellet Plant</a></li>
          <li><a href="Poultry-Mash-Plant.html">Poultry Mash Plant</a></li>
          <li><a href="Poultry-Mash-Machinery.html">Poultry Mash Machinery</a></li>
          <li><a href="cattle-feed-set.html">Cattle Feed Set</a></li>
          <li><a href="feed-additives.html">Feed Additives</a></li>
          <li><a href="animal-feed-machinery.html">Animal Feed Machinery</a></li>
          <li><a href="compound-feed-machinery.html">Compound Feed Machinery</a></li>
          <li><a href="feed-machinery.html">Feed Machinery</a></li>
          <li><a href="poultry-mash-feed-machine.html">Poultry Mash Feed Machine</a></li>
          <li><a href="pasture-pellet-mill.html">Pasture Pellet Mill</a></li>
          <li><a href="premix-feed-mill.html">Premix Feed Mill</a></li>
          <li><a href="premix-plant.html">Premix Plant</a></li>
          <li><a href="cattle-feed-mill.html">Cattle Feed Mill</a></li>
          <li><a href="pig-fed-mill.html">Pig Fed Mill</a></li>
          <li><a href="chicken-feed-mill.html">Chicken Feed Mill</a></li>
          <li><a href="fodder-machinery.html">Fodder Machinery</a></li>
          <li><a href="fodder-plant.html">Fodder Plant</a></li>
        </ul>

      </div>
      <br class="clear">
    </div>

    <div id="footer">
      <div id="foots">
        <div id="foot_logo"></div>
        <div id="copyright">
	  <ul>
            <li><a href="about.html">About Us</a>|</li>
            <li><a href="privacy-policy.html">Privacy Policy</a>|</li>
            <li><a href="terms-of-use.html">Terms of Use</a>|</li>
            <li><a href="faq.html">FAQ</a>|</li>
            <li><a href="enquiry.html">Enquiry</a>|</li>
            <li><a href="sitemap.html">Site Map</a>|</li>
            <li><a href="contact-us.html">Contact Us</a></li>
            <br class="clear">
          </ul>
          <div class="copyrights">© 1992-2009 <a href="index.html">Anyang Gemco Energy Machinery Co., Ltd.</a> All Rights Reserved.</div>
          <div class="links">Links: <a href="http://www.driedfruits.com.cn" title="Dried Fruits" target="_blank">Dried Fruits</a>,
            <a href="http://www.oilmillplant.com" title="Solvent Extraction Plant" target="_blank">Solvent Extraction</a>,
            <a href="http://www.oilseedspress.com" title="Oil Press" target="_blank">Oil Press</a>,
            <a href="http://www.biodiesel-machine.com" title="Biomass Briquette Press" target="_blank">Biomass Briquette Press</a>,
            <a href="http://www.chinarollforming.com" title="Roll Forming Machine" target="_blank">Roll Forming Machine</a>,
          </div>
        </div>
        <br class="clear">
      </div>
    </div>
<!-- 
    <jdoc:include type="message" />
    <jdoc:include type="component" />
 -->
  </body>
</html>
