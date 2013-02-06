<?php defined('_JEXEC') or die; ?>

<?php $count = 0 ?>

<ul class="recommend_product<?php echo $suffix ?>">
  <?php foreach ($products as $product):
                 $count = $count + 1 ?>
  <?php if ($is_background == "1"): ?>
  <li style="background:url(<?php echo $product->image_intro ?>) right bottom no-repeat;">
  <?php else: ?>
    <li <?php if ($count % 4 == 0) { echo "style='border-right: 0px;'"; }?>">
  <?php endif; ?>
    <h2><a href="<?php echo $product->url ?>"><?php echo $product->title ?></a></h2>
    <?php if ($is_background == "0"): ?>
    <div>
      <a href="<?php echo $product->url ?>">
        <img src="<?php echo $product->image_intro ?>" alt="<?php echo $product->title ?>" 
             border="0" height="<?php echo $height ?>" width="<?php echo $width ?>">
      </a>
    </div>
    <?php endif; ?>

    <?php echo $product->introtext; ?>

    <?php if ($is_background == "1"): ?>
    <div>
      <a href="<?php echo $product->url ?>">
        <img src="templates/wwl/images/learnmore.jpg" border="0" height="27" width="129">
      </a>
    </div>
    <?php endif; ?>
  </li>
  <?php endforeach; ?>
</ul>