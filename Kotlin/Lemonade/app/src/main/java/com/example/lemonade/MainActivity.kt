package com.example.lemonade

import android.os.Bundle
import android.support.v4.os.IResultReceiver.Default
import android.widget.Space
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.sizeIn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
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
    Surface(
        modifier = Modifier.fillMaxSize(),
        color = MaterialTheme.colorScheme.background
    ) {
        var imageResource = when(currentStep) {
            1 -> R.drawable.lemon_tree
            2 -> R.drawable.lemon_squeeze
            3 -> R.drawable.lemon_drink
            else -> R.drawable.lemon_restart
        }
        var textResource = when(currentStep) {
            1 -> R.string.Tree
            2 -> R.string.Lemon
            3 -> R.string.Glass_of_lemonade
            else -> R.string.Empty_glass
        }
        var content : String = when(currentStep) {
            1 -> "lemon_tree"
            2 -> "lemon_squeeze"
            3 -> "lemon_drink"
            else -> "lemon_restart"
    }
        Column(
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center
        ) {
            Box(
                Modifier
                    .size(240.dp, 240.dp)
                    .clip(RoundedCornerShape(32.dp))
                    .background(Color(0xFFCAEDB9))
            ) {
                Image(
                    painter = painterResource(id = imageResource),
                    contentDescription = content,
                    modifier = Modifier
                        .align(Alignment.Center)
                        .clickable {
                            currentStep = (currentStep + 1) % 4
                        }
                )
            }
            Spacer(modifier = Modifier.height(32.dp))
            Text(
                stringResource(id = textResource),
                fontSize = 18.sp
            )
        }
    }
}

@Preview(showBackground = true)
@Composable
fun DefaultPreview() {
    LemonadeTheme {
        LemonApp()
    }
}