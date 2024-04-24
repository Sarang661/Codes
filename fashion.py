fashion.py
from tensorflow import keras
import numpy as np 
import matplotlib.pyplot as plt 

fashion_mnist = keras.datasets.fashion_mnist
(train_img, train_labels), (test_img, test_labels) = fashion_mnist.load_data()

train_img = train_img / 255.0
test_img = test_img / 255.0

print(train_img.shape)
print(train_labels.shape)

model = keras.Sequential([  keras.layers.Flatten(), 
    keras.layers.Dense(128, activation='relu'),
    keras.layers.Dense(10, activation='softmax')])

model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', 
    metrics=['accuracy'])

# Train the model
print("hi")
print(train_img.shape)
print(train_labels.shape)
model.fit(train_img, train_labels, epochs=1)
#Evaluate the model
test_loss, test_acc = model.evaluate(test_img, test_labels)

print('Test accuracy:', test_acc)
# Make predictions
predictions = model.predict(test_img) 
predicted_labels =np.argmax(predictions, axis=1)
# Show some example images and their predicted labels
num_rows = 5
num_cols = 5
num_images = num_rows * num_cols 
plt.figure(figsize=(2 * 2 *num_cols, 2 * num_rows))
for i in range(num_images):
    plt.subplot(num_rows, 2 * num_cols, 1) 
    plt.imshow(test_img[i], cmap='gray')
    plt.axis('off')
    plt.subplot(num_rows, 2 * num_cols, 2) 
    plt.bar(range(10),predictions[i]) 
    plt.xticks(range(10))
    plt.ylim([0, 1])
    plt.tight_layout()
    plt.title(f"Predicted label: {predicted_labels[i]}")
    plt.show()












    