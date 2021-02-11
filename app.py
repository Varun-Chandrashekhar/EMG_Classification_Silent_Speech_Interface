# Import the Libraries
# Work with Data - the main Python libraries
import streamlit as st
import numpy as np
import pandas as pd
from PIL import Image, ImageOps  # Image processing
import pickle
##############################################################################################################
#@st.cache(suppress_st_warning=True)
def beginSetup():
    # Create a title and a sub-title
    st.write("""
    # EMG Based Silent Speech Interface
    Helps Predict Speech communicated by paralyzed individuals using  Machine Learning
    """)

    # Open and Display an Image
    image = Image.open('SSI_Image.png')
    st.image(image, use_column_width=True)  # caption = 'ML',

    # SIDEBAR
    st.sidebar.header('User Input Features')
    # st.sidebar.markdown("""
    # [Example CSV input file](https://raw.githubusercontent.com/dataprofessor/data/master/penguins_example.csv)
    # """)
###############################################################################################################
#@st.cache(suppress_st_warning=True)
def dataFrameComputation():
    # Collects user input features into dataframe
    uploaded_file = 'signal.csv'

    input_df = pd.read_csv(uploaded_file)

    # Displays the user input features
    st.subheader('User Input features')
    st.write(input_df)

    # This will be useful for the encoding phase
    with st.spinner('Processing CSV.....'):
        letters_raw = pd.read_csv('ML_Pattern_Recognition_Data V2.csv')
        try:
            letters = letters_raw.drop(columns=['Letter'])
        except:
            letters = letters_raw

    df = pd.concat([input_df, letters], axis=0)

    df = df[:1]  # Selects only the first row (the user input data)

    with st.spinner('Loading Model.....'):
        # Reads in saved classification model
        load_clf = pickle.load(open('EMG_clf.pkl', 'rb'))
    with st.spinner('Making Prediction.....'):
        # Apply model to make predictions
        prediction = load_clf.predict(df)
        prediction_proba = load_clf.predict_proba(df)

    st.subheader('Prediction')
    prediction = str(prediction)

    if prediction == '[[\'A\']]':
        n = 0
        prediction = 'A'
    elif prediction == '[[\'B\']]':
        n = 1
        prediction = 'Blank'
    elif prediction == '[[\'E\']]':
        n = 2
        prediction = 'E'
    elif prediction == '[[\'I\']]':
        n = 3
        prediction = 'I'
    elif prediction == '[[\'O\']]':
        n = 4
        prediction = 'O'
    elif prediction == '[[\'U\']]':
        n = 5
        prediction = 'U'

    prediction_proba = prediction_proba[0][n]
    prediction_proba = prediction_proba * 100
    prediction_proba = str(prediction_proba) + '%'

    st.success(prediction)

    st.subheader('Prediction Probability')
    st.success(prediction_proba)
################################################################################################################
#@st.cache(suppress_st_warning=True)
def endSetup():
    # Open and Display an Image
    image = Image.open('device.jfif')
    st.image(image, use_column_width=True, caption = 'Created Silent Speech Interface')

    st.subheader('Training Data')
    with st.spinner('Loading Large CSV.....'):
        letters_raw = pd.read_csv('ML_Pattern_Recognition_Data V2.csv') # repeated
        st.write(letters_raw)
################################################################################################################
beginSetup() # Calling Function

button = st.sidebar.button("Rerun Program with New EMG Signal")
if(button==1):
    import Signal_CSV_load
    button=0

dataFrameComputation()



endSetup()
