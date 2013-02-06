<?php defined('_JEXEC') or die; ?>

<?php $count = 0 ?>

<ul class="product_view">
  <?php foreach ($products as $product):
                 $count = $count + 1 ?>
  <li>
    <div>
      <a href="<?php echo $product->urla ?>">
        <img src="<?php echo $product->image_intro ?>" alt="<?php echo $product->title ?>" 
             border="0" height="<?php echo $height ?>" width="<?php echo $width ?>">
      </a>
    </div>
    <h2><a href="<?php echo $product->urla ?>"><?php echo $product->title ?></a></h2>
  </li>
  <?php endforeach; ?>
</ul>