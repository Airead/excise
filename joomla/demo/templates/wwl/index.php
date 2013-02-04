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
      <jdoc:include type="modules" name="wwl-product-list" />
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
