package com.example.lemonade

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.getValue
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.painter.Painter
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.lemonade.ui.theme.LemonadeTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            LemonadeTheme {
                LemonApp()
            }
        }
    }
}

@Composable
fun LemonApp() {
    // A surface container using the 'background' color from the theme
    var currentStep by remember { mutableStateOf(1) }
    var squeezeStep by remember { mutableStateOf(1) }
    Surface(
        modifier = Modifier.fillMaxSize(),
        color = MaterialTheme.colorScheme.background
    ) {
        when(currentStep) {
            1 -> {
                LemonTextAndImage(
                    painter = painterResource(id = R.drawable.lemon_tree),
                    contentDescription = "lemon_tree",
                    textContent = stringResource(id = R.string.Tree),
                    onImageClicked = {
                        currentStep = (currentStep + 1) % 4
                        squeezeStep = (2..4).random()
                    }
                )
            }
            2 -> {
                LemonTextAndImage(
                    painter = painterResource(id = R.drawable.lemon_squeeze),
                    contentDescription = "lemon_tree",
                    textContent = stringResource(id = R.string.Lemon),
                    onImageClicked = {
                        when(squeezeStep) {
                            in 2..4 -> squeezeStep--
                            else -> currentStep =(currentStep + 1) % 4
                        }
                    }
                )
            }
            3 -> {
                LemonTextAndImage(
                    painter = painterResource(id = R.drawable.lemon_drink),
                    contentDescription = "lemon_drink",
                    textContent = stringResource(id = R.string.Glass_of_lemonade),
                    onImageClicked = {
                        currentStep = (currentStep + 1) % 4
                    }
                )
            }
            0 -> {
                LemonTextAndImage(
                    painter = painterResource(id = R.drawable.lemon_restart),
                    contentDescription = "lemon_restart",
                    textContent = stringResource(id = R.string.Empty_glass),
                    onImageClicked = {
                        currentStep = (currentStep + 1) % 4
                    }
                )
            }
        }
    }
}

@Composable
fun LemonTextAndImage(
    painter: Painter,
    contentDescription: String,
    textContent: String,
    onImageClicked: () -> Unit
) {
    Column(
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Box(
            Modifier
                .size(240.dp, 240.dp)
                .border(2.dp, Color(185, 228, 160), RoundedCornerShape(32.dp) )
                .clip(RoundedCornerShape(32.dp))
                .background(Color(0xFFCAEDB9))
        ) {
            Image(
                painter = painter,
                contentDescription = contentDescription,
                modifier = Modifier
                    .align(Alignment.Center)
                    .clickable {
                        onImageClicked()
                    }
            )
        }
        Spacer(modifier = Modifier.height(32.dp))
        Text(
            textContent,
            fontSize = 18.sp
        )
    }
}

@Preview(showBackground = true)
@Composable
fun DefaultPreview() {
    LemonadeTheme {
        LemonApp()
    }
}